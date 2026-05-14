# Day 3 学习记录

## 学习目标
- 先理解 LLM 输入链路：文本 -> tokens -> input_ids

## 实验脚本
- `python scripts/tokenizer_lab.py`
- `python scripts/tokenizer_lab.py "我正在 learn tokenization"`

## 实验 1：中文
文本：今天天气很好

tokens: ['[CLS]', '今', '天', '天', '气', '很', '好', '[SEP]']

input_ids: [101, 791, 1921, 1921, 3698, 2523, 1962, 102]

## 实验 2：英文
文本：The weather is good today.

tokens: ['[CLS]', '[UNK]', 'we', '##ather', 'is', 'good', 'today', '.', '[SEP]']

input_ids: [101, 100, 8997, 12290, 8310, 9005, 11262, 119, 102]

## 实验 3：中英混合
文本：我正在 learn tokenization

tokens: ['[CLS]', '我', '正', '在', 'le', '##ar', '##n', 'to', '##ken', '##i', '##za', '##tion', '[SEP]']

input_ids: [101, 2769, 3633, 1762, 8983, 8458, 8171, 8228, 11285, 8169, 9283, 8361, 102]

## 当前理解
- 模型真正处理的是 input_ids，不是原始文本
- tokens 更适合人类观察 tokenizer 的切分结果
- [CLS] / [SEP] 是 special tokens
- ## 表示 continuation token，不是临时符号
- tokenizer 会按词表和规则切分，不一定按“字”或“完整单词”切

## 下一步问题
- 如何从 tokenization 过渡到 chunking、embedding、retrieval 和 RAG 主链路？
