# Day 08 - 用真实文档构建知识库

**日期：** 2026-05-10

---

## 学习目标

- 用真实 Markdown 文件替换之前的测试文本，构建有意义的知识库
- 理解文档预处理流水线：读取 → 切块 → 向量化 → 存库
- 掌握 ChromaDB 的 metadata 字段，记录每个 chunk 的来源文件
- 把构建知识库（build）和查询使用（pipeline）拆成独立脚本

---

## 实验结果

> 运行 `conda activate rag-learn && python scripts/build_knowledge_base.py`

**切块统计（max_chunk_size=300）：**

| 文件 | chunk 数 |
|------|----------|
| day03.md | 4 |
| day04.md | 5 |
| day05.md | 4 |
| day06.md | 4 |
| day07.md | 5 |
| **合计** | **22** |

**ChromaDB 写入：** `collection=kb_real`，共 22 条

**观察：**
- chunk 数量和文件长度大致成比例吗？
- sentence-aware 切法和 max_chunk_size=300 搭配效果如何？有没有太短的 chunk？

---

## 当前理解

> 用自己的话解释，不看资料能说清楚最好

- **为什么构建知识库和查询要拆成两个脚本：**

- **ChromaDB 的 metadata 字段有什么用途：**
  记录每个 chunk 的来源（source 字段），检索后可以告知用户"参考了哪篇文档"

- **sentence-aware chunking 和 character chunking 在这个场景下各有什么优缺点：**

- **max_chunk_size 越小，对检索有什么影响：**

---

## 下一步问题

- [ ] 如何在检索结果里附带 source 信息，让 LLM 的回答注明来源？
- [ ] 知识库更新时（新增文档）如何做增量写入，而不是全量重建？
- [ ] 不同的切块粒度（100 / 300 / 500）对检索效果影响如何？
- [ ] 如何对 RAG 系统做定量评估（而非靠感觉判断好坏）？
