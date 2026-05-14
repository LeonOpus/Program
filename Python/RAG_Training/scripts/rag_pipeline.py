"""
Day 07 - RAG Pipeline
检索增强生成：向量检索 + 本地 LLM（llama-cpp-python）
LLM 模型必须是 GGUF 格式，通过环境变量 LLAMA_MODEL_PATH 指定路径
"""

import os
import sys
import chromadb
from llama_cpp import Llama
from sentence_transformers import SentenceTransformer

EMBED_MODEL_PATH = "/home/leon/Model/ModelScope/sentence-transformers/paraphrase-multilingual-MiniLM-L12-v2"
DB_PATH = "data/chroma_db"
COLLECTION_NAME = "kb_real"

# GGUF 模型路径从环境变量读取，方便切换不同模型
# 示例：export LLAMA_MODEL_PATH=/home/leon/Model/ModelScope/qwen2.5-7b-instruct/qwen2.5-7b-instruct-q4_k_m.gguf
LLAMA_MODEL_PATH = os.environ.get("LLAMA_MODEL_PATH", "")

# ── 1. 加载模型 ───────────────────────────────────────────────
if not LLAMA_MODEL_PATH:
    print("错误：未设置环境变量 LLAMA_MODEL_PATH")
    print("示例：export LLAMA_MODEL_PATH=/home/leon/Model/ModelScope/qwen2.5-7b/qwen2.5-7b-q4_k_m.gguf")
    sys.exit(1)

print("加载 Embedding 模型...")
embed_model = SentenceTransformer(EMBED_MODEL_PATH)

print("加载 LLM（llama.cpp）...")
# n_ctx：上下文窗口大小；n_gpu_layers=-1 表示全部层放 GPU，无 GPU 时设 0
llm = Llama(model_path=LLAMA_MODEL_PATH, n_ctx=2048, n_gpu_layers=-1, verbose=False)


def get_embedding(texts: list[str]) -> list[list[float]]:
    return embed_model.encode(texts).tolist()


# ── 2. 连接向量库 ─────────────────────────────────────────────
# 知识库由 build_knowledge_base.py 负责构建，此处只读取
client = chromadb.PersistentClient(path=DB_PATH)
if COLLECTION_NAME not in [c.name for c in client.list_collections()]:
    print(f"错误：向量库中不存在 collection '{COLLECTION_NAME}'")
    print("请先运行：python scripts/build_knowledge_base.py")
    sys.exit(1)

collection = client.get_collection(COLLECTION_NAME)
print(f"已连接向量库，共 {collection.count()} 条文档")


# ── 3. 检索函数 ───────────────────────────────────────────────
def retrieve(question: str, top_k: int = 3) -> list[dict]:
    results = collection.query(
        query_embeddings=get_embedding([question]),
        n_results=top_k,
        include=["documents", "distances"],
    )
    chunks = []
    for doc, dist in zip(results["documents"][0], results["distances"][0]):
        chunks.append({"text": doc, "similarity": round(1 - dist, 4)})
    return chunks


# ── 4. 构建 Prompt ────────────────────────────────────────────
def build_prompt(question: str, chunks: list[dict]) -> str:
    refs = "\n".join(f"- {c['text']}" for c in chunks)
    return f"""你是一个技术助手，请根据以下参考内容回答问题。
如果参考内容不足以回答，请直接说不知道，不要编造。

参考内容：
{refs}

问题：{question}"""


# ── 5. 主流程 ─────────────────────────────────────────────────
question = input("\n请输入问题：").strip()
if not question:
    print("问题不能为空")
    sys.exit(1)

print("\n" + "=" * 60)
print(f"【问题】{question}")

# 检索
chunks = retrieve(question)
print("\n【检索到的 Chunk】")
for i, c in enumerate(chunks, 1):
    print(f"  Top{i}  相似度={c['similarity']}  |  {c['text']}")

# 生成
prompt = build_prompt(question, chunks)
print("\n【LLM 回答】")
response = llm.create_chat_completion(
    messages=[{"role": "user", "content": prompt}],
    temperature=0.7,
    max_tokens=512,
)
print(response["choices"][0]["message"]["content"])

# 运行方式：
#   export LLAMA_MODEL_PATH=/home/leon/Model/ModelScope/<模型目录>/<模型文件>.gguf
#   conda activate rag-learn && python scripts/rag_pipeline.py
#
# 模型需为 GGUF 格式，推荐从 ModelScope 下载量化版本，例如：
#   Qwen2.5-7B-Instruct-GGUF / qwen2.5-7b-instruct-q4_k_m.gguf
