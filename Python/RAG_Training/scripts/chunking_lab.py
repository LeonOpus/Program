from __future__ import annotations

import argparse

DEFAULT_TEXT = (
    "今天我们做一个最小 chunking 实验，"
    "目标是先看清楚文本如何被切成多个片段。"
    "Then we compare chunk sizes and overlap settings, "
    "so we can observe trade-offs before moving to embedding and retrieval."
)
DEFAULT_CHUNK_SIZE = 40
DEFAULT_OVERLAP = 10


def chunk_text(text: str, chunk_size: int, overlap: int) -> list[dict]:
    if chunk_size <= 0:
        raise ValueError("chunk_size 必须 > 0")
    if overlap < 0:
        raise ValueError("overlap 必须 >= 0")
    if overlap >= chunk_size:
        raise ValueError("overlap 必须 < chunk_size")

    step = chunk_size - overlap
    chunks: list[dict] = []

    for index, start in enumerate(range(0, len(text), step)):
        end = min(start + chunk_size, len(text))
        chunks.append(
            {
                "index": index,
                "start": start,
                "end": end,
                "content": text[start:end],
            }
        )
        if end == len(text):
            break

    return chunks


def chunk_text_by_sentence(text: str, max_chunk_size: int) -> list[dict]:
    if max_chunk_size <= 0:
        raise ValueError("max_chunk_size 必须 > 0")

    sentence_end_chars = {"。", "！", "？", ".", "!", "?"}
    sentences: list[tuple[int, int, str]] = []
    start = 0

    for i, char in enumerate(text):
        if char in sentence_end_chars:
            end = i + 1
            sentence = text[start:end]
            if sentence.strip():
                sentences.append((start, end, sentence))
            start = end

    if start < len(text):
        sentence = text[start:]
        if sentence.strip():
            sentences.append((start, len(text), sentence))

    chunks: list[dict] = []
    current_start = 0
    current_end = 0
    current_content = ""

    def pick_split_len(text_piece: str, limit: int) -> int:
        # 超长句 fallback：优先在可容纳范围内按空格切分，找不到再硬切
        split_at = text_piece.rfind(" ", 1, limit + 1)
        if split_at != -1:
            return split_at + 1
        return limit

    def flush_current() -> None:
        nonlocal current_start, current_end, current_content
        if not current_content:
            return
        chunks.append(
            {
                "index": len(chunks),
                "start": current_start,
                "end": current_end,
                "content": current_content,
            }
        )
        current_start = 0
        current_end = 0
        current_content = ""

    for sent_start, _, sentence in sentences:
        remaining_start = sent_start
        remaining_text = sentence

        while remaining_text:
            if not current_content:
                current_start = remaining_start

            space_left = max_chunk_size - len(current_content)
            if space_left <= 0:
                flush_current()
                continue

            if len(remaining_text) <= space_left:
                current_content += remaining_text
                current_end = remaining_start + len(remaining_text)
                remaining_text = ""
            else:
                split_len = pick_split_len(remaining_text, space_left)
                piece = remaining_text[:split_len]
                current_content += piece
                current_end = remaining_start + len(piece)
                remaining_text = remaining_text[split_len:]
                remaining_start += split_len
                flush_current()

    flush_current()
    return chunks


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Chunking demo")
    parser.add_argument("chunk_size", nargs="?", type=int, default=DEFAULT_CHUNK_SIZE)
    parser.add_argument("overlap", nargs="?", type=int, default=DEFAULT_OVERLAP)
    return parser.parse_args()


def main() -> None:
    args = parse_args()

    try:
        char_chunks = chunk_text(DEFAULT_TEXT, args.chunk_size, args.overlap)
        sentence_chunks = chunk_text_by_sentence(DEFAULT_TEXT, args.chunk_size)
    except ValueError as error:
        print(f"参数错误: {error}")
        return

    print(f"原始文本长度: {len(DEFAULT_TEXT)}")
    print(f"chunk_size: {args.chunk_size}")
    print(f"overlap: {args.overlap}")
    print()

    print("=== character-based chunking ===")
    print(f"chunk 总数: {len(char_chunks)}")
    for chunk in char_chunks:
        print(
            f"[{chunk['index']}] chars[{chunk['start']}:{chunk['end']}] "
            f"{chunk['content']}"
        )
    print()

    print("=== sentence-aware chunking ===")
    print(f"chunk 总数: {len(sentence_chunks)}")
    for chunk in sentence_chunks:
        print(
            f"[{chunk['index']}] chars[{chunk['start']}:{chunk['end']}] "
            f"{chunk['content']}"
        )


if __name__ == "__main__":
    main()
