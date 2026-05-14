from __future__ import annotations

import sys

from transformers import AutoTokenizer

DEFAULT_MODEL = "bert-base-chinese"
DEFAULT_TEXT = "今天天气很好"


def main() -> None:
    text = " ".join(sys.argv[1:]).strip() or DEFAULT_TEXT
    tokenizer = AutoTokenizer.from_pretrained(DEFAULT_MODEL)
    input_ids = tokenizer.encode(text, add_special_tokens=True)
    tokens = tokenizer.convert_ids_to_tokens(input_ids)

    print(f"原始文本: {text}")
    print(f"tokens: {tokens}")
    print(f"input_ids: {input_ids}")


if __name__ == "__main__":
    main()
