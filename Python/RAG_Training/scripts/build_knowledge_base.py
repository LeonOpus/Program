"""
Day 08 - Build Knowledge Base
读取 data/docs/ 下的 Markdown 文件，切块后存入 ChromaDB
"""

import sys
sys.path.insert(0, "scripts")  # 让 import chunking_lab 能找到同目录模块

from pathlib import Path
import chromadb
from sentence_transformers import SentenceTransformer
from chunking_lab import chunk_text_by_sentence

import re

DOCS_DIR = Path("data/docs")
DB_PATH = "data/chroma_db"
COLLECTION_NAME = "kb_real"
MAX_CHUNK_SIZE = 300
EMBED_MODEL_PATH = "/home/leon/Model/ModelScope/sentence-transformers/paraphrase-multilingual-MiniLM-L12-v2"

def clean_markdown(text: str) -> str:
    # 删除代码块（``` 包裹的内容，含跨行）
    text = re.sub(r"```.*?```", "", text, flags=re.DOTALL)
    lines = text.splitlines()
    cleaned = []
    for line in lines:
        stripped = line.strip()
        if stripped.startswith("|"):   # 表格行
            continue
        if stripped.startswith(">"):   # 模板占位符 / blockquote
            continue
        cleaned.append(line)
    # 合并连续超过2个空行为最多2个
    text = "\n".join(cleaned)
    text = re.sub(r"\n{3,}", "\n\n", text)
    return text.strip()


# ── 1. 读取并切块 ──────────────────────────────────────────────
md_files = sorted(DOCS_DIR.glob("*.md"))
if not md_files:
    print(f"错误：{DOCS_DIR} 下没有找到 .md 文件")
    sys.exit(1)

all_chunks: list[dict] = []  # {"id": str, "text": str, "source": str}

for md_file in md_files:
    text = clean_markdown(md_file.read_text(encoding="utf-8"))
    chunks = chunk_text_by_sentence(text, MAX_CHUNK_SIZE)
    print(f"  {md_file.name}: {len(chunks)} 块")
    for c in chunks:
        all_chunks.append({
            "id": f"{md_file.stem}_chunk{c['index']}",
            "text": c["content"].strip(),
            "source": md_file.name,
        })

# 过滤掉切出来的空块
all_chunks = [c for c in all_chunks if c["text"]]
print(f"\n总计：{len(md_files)} 个文件，{len(all_chunks)} 个有效 chunk")

# ── 2. 生成向量 ───────────────────────────────────────────────
print("\n加载 Embedding 模型...")
model = SentenceTransformer(EMBED_MODEL_PATH)
embeddings = model.encode([c["text"] for c in all_chunks]).tolist()

# ── 3. 写入 ChromaDB ──────────────────────────────────────────
client = chromadb.PersistentClient(path=DB_PATH)

# 删除旧 collection（重建知识库时保持幂等）
if COLLECTION_NAME in [c.name for c in client.list_collections()]:
    client.delete_collection(COLLECTION_NAME)

collection = client.create_collection(
    name=COLLECTION_NAME,
    metadata={"hnsw:space": "cosine"},
)
collection.add(
    ids=[c["id"] for c in all_chunks],
    documents=[c["text"] for c in all_chunks],
    embeddings=embeddings,
    metadatas=[{"source": c["source"]} for c in all_chunks],
)

print(f"已写入 ChromaDB：collection={COLLECTION_NAME}，共 {collection.count()} 条")

# 运行方式：
#   conda activate rag-learn && python scripts/build_knowledge_base.py
