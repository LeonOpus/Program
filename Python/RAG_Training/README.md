# llm-engineering-30days

## 项目介绍
30 天 LLM 工程学习计划项目，用来逐步完成一个可运行、可理解、可复用的 LLM 工程学习样例。

## 当前进度
- Day 1：完成 FastAPI 最小骨架
- Day 2：完成项目基础分层、config 和 logging
- Day 3：开始 tokenization 实验
- Day 5：Embedding 与余弦相似度实验
- Day 6：ChromaDB 向量存储与检索
- Day 7：RAG 完整链路（llama-cpp-python + 本地 GGUF 模型）

## 项目结构
```text
llm-engineering-30days/
├── app/
│   ├── api/
│   ├── core/
│   └── main.py
├── data/
│   └── chroma_db/          # ChromaDB 持久化向量库
├── docs/
│   └── journal/
│       ├── day03.md
│       ├── day04.md
│       ├── day05.md
│       ├── day06.md
│       └── day07.md
├── scripts/
│   ├── tokenizer_lab.py
│   ├── chunking_lab.py
│   ├── embedding_lab.py
│   ├── vectorstore_lab.py
│   └── rag_pipeline.py
├── .gitignore
├── README.md
└── requirements.txt
```

## 环境准备

使用 miniconda 管理环境，不动 base：

```bash
conda create -n rag-learn python=3.11 -y
conda activate rag-learn
python -m pip install sentence-transformers chromadb
```

> **注意**：始终使用 `python -m pip install` 而非裸 `pip install`，
> 确保包装入 conda 环境而非系统 Python。

### llama-cpp-python 安装（支持 CUDA / RTX 3090）

```bash
# 1. 安装编译依赖（conda nvidia 频道）
conda install -n rag-learn -c nvidia cuda-nvcc libcublas-dev -y

# 2. 源码编译，启用 CUDA 后端
CMAKE_ARGS="-DGGML_CUDA=on" python -m pip install llama-cpp-python --upgrade
```

编译成功后会识别 RTX 3090（24 GB VRAM），`n_gpu_layers=-1` 时全部层放 GPU。

### GGUF 模型准备

`scripts/rag_pipeline.py` 需要本地 GGUF 格式模型，推荐从 ModelScope 下载量化版本，
统一存放到 `/home/leon/Model/ModelScope/`：

```bash
conda activate rag-learn
python -c "
from modelscope import snapshot_download
snapshot_download('Qwen/Qwen2.5-7B-Instruct-GGUF',
                  cache_dir='/home/leon/Model/ModelScope')
"
```

运行前设置模型路径：

```bash
export LLAMA_MODEL_PATH=/home/leon/Model/ModelScope/Qwen/Qwen2.5-7B-Instruct-GGUF/qwen2.5-7b-instruct-q4_k_m.gguf
```

FastAPI 服务依赖（独立安装或加入同一环境）：
```bash
python -m pip install -r requirements.txt
```

## 启动服务
```bash
conda activate rag-learn
uvicorn app.main:app --reload
```

服务默认运行在：`http://127.0.0.1:8000`

## 健康检查
```bash
curl http://127.0.0.1:8000/health
```

期望返回：`{"status":"ok"}`

## 实验脚本

```bash
conda activate rag-learn

python scripts/embedding_lab.py
python scripts/vectorstore_lab.py

export LLAMA_MODEL_PATH=/home/leon/Model/ModelScope/<模型目录>/<模型>.gguf
python scripts/rag_pipeline.py
```

## 学习记录入口
- Day 3：`docs/journal/day03.md`
- Day 4：`docs/journal/day04.md`
- Day 5：`docs/journal/day05.md`
- Day 6：`docs/journal/day06.md`
- Day 7：`docs/journal/day07.md`

## 当前学习目标
- 先理解 LLM 输入链路：文本 -> tokens -> input_ids
- 再进入 chunking、embedding、retrieval 和 RAG 主链路
