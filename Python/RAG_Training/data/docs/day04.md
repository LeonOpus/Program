# Day 4 学习记录

## 学习目标
- 用最小实验理解字符级 chunking 的基本行为
- 观察 `chunk_size` 和 `overlap` 对分块结果的影响

## chunking 是什么
- chunking 是把一段较长文本切成多个较短片段，便于后续处理。

## 为什么需要 overlap
- overlap 让相邻 chunk 共享一部分内容，减少关键信息刚好落在边界时的割裂。

## 本次实验脚本说明
- 脚本：`scripts/chunking_lab.py`
- 核心函数：`chunk_text(text: str, chunk_size: int, overlap: int) -> list[dict]`
- 新增函数：`chunk_text_by_sentence(text: str, max_chunk_size: int) -> list[dict]`
- 本次只做字符级 chunking，不涉及 token-based chunking、embedding。
- 脚本运行时会输出两部分结果：`character-based chunking` 和 `sentence-aware chunking`。

## 运行命令
```bash
python scripts/chunking_lab.py 40 0
python scripts/chunking_lab.py 40 10
```

可选扩展实验：
```bash
python scripts/chunking_lab.py 25 5
```

## 建议观察点
- `chunk_size` 变小后，chunk 总数如何变化
- `overlap` 增大后，相邻 chunk 的重复内容如何变化
- 最后一块 chunk 的长度和内容是否完整
- 边界处的句子或英文单词是否被截断

## 实验记录

### 实验 1：chunk_size=40, overlap=0
- 共切出 5 个 chunk
- 相邻 chunk 之间没有共享内容
- 文本在边界处被硬切开
- 英文内容会被直接按字符截断，不保证单词完整

### 实验 2：chunk_size=40, overlap=10
- 共切出 6 个 chunk
- 相邻 chunk 之间共享 10 个字符
- 边界附近的上下文被重复保留
- 这样更不容易丢失边界信息，但会带来重复内容
- 即使有 overlap，字符级 chunking 仍然可能把英文单词截断

### 当前结论
- overlap 的作用是减少 chunk 边界造成的信息断裂
- overlap 会增加 chunk 数量和重复内容
- 字符级 chunking 适合理解原理，但不等于真实 RAG 中最理想的切块方式

## 字符级与句子边界优先对比（最小增强）
- 字符级切块容易在边界处硬切，句子语义和英文单词都可能被截断。
- 句子边界优先切块会尽量按句子边界拼接，减少边界处语义断裂。
- 它的局限是 chunk 长度可能不均匀；当单句过长时，仍可能被拆分。

## 本次改进
- 之前的 sentence-aware 版本在超长句子下，仍会退化成字符级截断。
- 现在增加了 fallback：超长句优先在当前可容纳范围内按空格切分，找不到合适空格才硬切。
- 这比纯字符硬切更自然，但仍不是最终形态。
