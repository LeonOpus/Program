# Day 07 - RAG Pipeline 完整链路

**日期：** 2026-05-10

---

## 学习目标

- 把 Day5（Embedding）+ Day6（向量检索）+ 本地 LLM 串成一条完整 RAG 链路
- 理解 Prompt 构造对生成质量的影响
- 体验"参考内容不足时 LLM 如何应对"的边界行为
- 为后续扩展（多文档、流式输出、评估）打基础

---

## 实验结果

> 前提：已准备好 GGUF 格式模型，并设置环境变量
> ```bash
> export LLAMA_MODEL_PATH=/home/leon/Model/ModelScope/<模型目录>/<模型>.gguf
> conda activate rag-learn && python scripts/rag_pipeline.py
> ```

**检索结果（问题："vLLM 是如何解决显存碎片化问题的？"）：**

| 排名 | 相似度 | Chunk 内容 |
|------|--------|------------|
| Top1 | 0.6108 | 与 vLLM 相比，传统推理框架在显存管理上效率较低，容易造成显存碎片化。 |
| Top2 | 0.6074 | vLLM 是一个高吞吐量的大语言模型推理框架，支持 PagedAttention 技术。 |
| Top3 | 0.5643 | vLLM uses PagedAttention to efficiently manage GPU memory during LLM inference. |

**LLM 回答：**

```
# 粘贴 LLM 的实际输出
```

**观察：**
- LLM 回答是否准确引用了 chunk 中的信息？
- 对于知识库中没有的细节，LLM 是否如实说"不知道"？
- 回答的语言风格和长度是否合适？

---

## 当前理解

> 用自己的话解释，不看资料能说清楚最好

- **RAG 和直接问 LLM 的区别：**

- **Prompt 中"如果不足请说不知道"这句话的作用：**

- **检索质量如何影响最终回答质量：**

- **当前知识库只有5句话，覆盖面很窄，会产生什么问题：**

---

## 下一步问题

- [ ] 如果知识库有几千篇文档，chunk 怎么切、怎么管理？
- [ ] 相似度阈值过滤：低于某个分数的 chunk 不送给 LLM，怎么设定合理阈值？
- [ ] 流式输出（streaming）怎么接入，让回答逐字打印？
- [ ] 怎么评估 RAG 的回答质量？有哪些自动化评估方法（RAGAS 等）？
- [ ] Reranker 是什么？为什么检索后还需要重排序？
