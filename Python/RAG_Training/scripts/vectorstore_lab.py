"""
Day 06 - Vector Store Lab
用 ChromaDB 存储文本向量，并做语义检索
"""

import chromadb
from sentence_transformers import SentenceTransformer

MODEL_PATH = "/home/leon/Model/ModelScope/sentence-transformers/paraphrase-multilingual-MiniLM-L12-v2"
DB_PATH = "data/chroma_db"
COLLECTION_NAME = "vllm_docs"

# 复用 Day5 的5句测试文本
sentences = [
    "vLLM 是一个高吞吐量的大语言模型推理框架，支持 PagedAttention 技术。",
    "vLLM uses PagedAttention to efficiently manage GPU memory during LLM inference.",
    "与 vLLM 相比，传统推理框架在显存管理上效率较低，容易造成显存碎片化。",
    "PagedAttention 借鉴操作系统虚拟内存分页思想，用于管理 KV Cache。",
    "今天天气不错，适合出去骑车。",
]
doc_ids = [f"doc_{i}" for i in range(len(sentences))]

# ── 1. 加载模型，生成向量 ──────────────────────────────────────
print("加载 Embedding 模型...")
model = SentenceTransformer(MODEL_PATH)
embeddings = model.encode(sentences).tolist()  # ChromaDB 接受 list[list[float]]

# ── 2. 初始化持久化 ChromaDB ──────────────────────────────────
client = chromadb.PersistentClient(path=DB_PATH)

# 每次运行前清空旧 collection，避免 ID 重复报错
client.delete_collection(COLLECTION_NAME) if COLLECTION_NAME in [
    c.name for c in client.list_collections()
] else None

collection = client.create_collection(
    name=COLLECTION_NAME,
    metadata={"hnsw:space": "cosine"},  # 用余弦距离
)

# ── 3. 写入文档 ───────────────────────────────────────────────
collection.add(
    ids=doc_ids,
    documents=sentences,
    embeddings=embeddings,
)
print(f"\n已写入 {collection.count()} 条文档到 {DB_PATH}")

# ── 4. 语义检索 ───────────────────────────────────────────────
query = "如何优化LLM推理时的显存使用"
query_embedding = model.encode([query]).tolist()

results = collection.query(
    query_embeddings=query_embedding,
    n_results=2,
    include=["documents", "distances"],
)

print("\n" + "=" * 60)
print(f"【查询】{query}")
print("=" * 60)
for rank, (doc, dist) in enumerate(
    zip(results["documents"][0], results["distances"][0]), start=1
):
    # ChromaDB cosine distance = 1 - cosine_similarity，转回相似度
    similarity = 1 - dist
    print(f"  Top{rank}  相似度={similarity:.4f}  |  {doc}")

# 运行方式：
#   conda activate rag-learn && python scripts/vectorstore_lab.py
