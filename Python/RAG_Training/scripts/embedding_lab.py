"""
Day 05 - Embedding Lab
学习 sentence-transformers 生成文本向量，并计算余弦相似度
模型：paraphrase-multilingual-MiniLM-L12-v2（支持中文）
"""

from sentence_transformers import SentenceTransformer
from sklearn.metrics.pairwise import cosine_similarity

# 加载多语言模型
# 优先用本地缓存（通过 ModelScope 下载）；若已联网也可直接用模型名
MODEL_PATH = "/home/leon/Model/ModelScope/sentence-transformers/paraphrase-multilingual-MiniLM-L12-v2"
model = SentenceTransformer(MODEL_PATH)

# 5句围绕 vLLM 推理框架的测试文本（中英文混合）
sentences = [
    "vLLM 是一个高吞吐量的大语言模型推理框架，支持 PagedAttention 技术。",
    "vLLM uses PagedAttention to efficiently manage GPU memory during LLM inference.",
    "与 vLLM 相比，传统推理框架在显存管理上效率较低，容易造成显存碎片化。",
    "PagedAttention 借鉴操作系统虚拟内存分页思想，用于管理 KV Cache。",
    "今天天气不错，适合出去骑车。",  # 故意放一句无关内容，观察相似度差异
]

# 生成向量
embeddings = model.encode(sentences)

print("=" * 60)
print("【向量维度】")
for i, (sent, emb) in enumerate(zip(sentences, embeddings)):
    print(f"  句{i+1}: shape={emb.shape}  |  {sent[:35]}...")

# 计算第1句与其余4句的余弦相似度
print("\n" + "=" * 60)
print("【余弦相似度】第1句 vs 其余各句")
ref = embeddings[0:1]  # shape (1, dim)
for i in range(1, len(sentences)):
    sim = cosine_similarity(ref, embeddings[i : i + 1])[0][0]
    print(f"  句1 vs 句{i+1}: {sim:.4f}  |  {sentences[i][:40]}...")

# 运行方式：
#   conda activate rag-learn && python scripts/embedding_lab.py
