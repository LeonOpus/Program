# Day 06 - Vector Store 与语义检索

**日期：** 2026-05-10

---

## 学习目标

- 理解向量数据库的作用：存储向量并支持近似最近邻（ANN）检索
- 掌握 ChromaDB 的基本用法：持久化存储、写入、查询
- 体验 RAG 检索链路的核心步骤：query → embedding → Top-K 检索
- 理解 cosine distance 与 cosine similarity 的转换关系

---

## 实验结果

> 运行 `conda activate rag-learn && python scripts/vectorstore_lab.py`

**检索结果（查询："如何优化LLM推理时的显存使用"）：**

| 排名 | 相似度 | 返回内容 |
|------|--------|----------|
| Top1 | 0.5517 | 与 vLLM 相比，传统推理框架在显存管理上效率较低，容易造成显存碎片化。 |
| Top2 | 0.5349 | vLLM uses PagedAttention to efficiently manage GPU memory during LLM inference. |

**观察：**

- 两个 Top 结果都与"显存管理"语义相关，检索方向正确
- Top1 是中文句，Top2 是英文句，说明多语言模型跨语言检索有效
- 无关句（"今天天气不错..."）未出现在结果中，过滤正常

---

## 当前理解

> 用自己的话解释，不看资料能说清楚最好

- **向量数据库解决什么问题：**

- **ChromaDB 的 cosine distance 和 cosine similarity 什么关系：**
  `similarity = 1 - distance`，ChromaDB 返回的是距离（越小越近）

- **RAG 检索的完整链路是什么：**
  文档切片 → embedding → 存入向量库 → 查询 embedding → Top-K 检索 → 送给 LLM 生成

- **为什么不直接暴力扫描所有向量：**

---

## 下一步问题

- [ ] HNSW 索引的原理是什么？它如何权衡召回率和速度？
- [ ] Top-K 的 K 怎么设定？相似度阈值要不要加过滤？
- [ ] 如果文档很长，切片策略（chunk size / overlap）如何影响检索质量？
- [ ] ChromaDB 和 FAISS 的区别是什么，什么场景用哪个？
- [ ] 检索出来的 Top-K chunk 怎么拼成 prompt 送给 LLM？
