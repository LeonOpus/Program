# Qwen3-MoE + LoRA 在昇腾 910B 上的运行时注入失败：根因分析与修复

## 背景
在验证 Qwen3-MoE 模型在昇腾环境下启用 LoRA 推理时，遇到运行时崩溃。
错误是 TypeError: 'NoneType' object is not callable。
根因是 GPU 与昇腾平台在 MoE LoRA 注入路径上的假设不一致。

## 环境信息
- 设备：Ascend 910B × 2，tensor_parallel_size=2
- vLLM：0.18.0
- vllm-ascend：0.17.0rc2
- 模型：Qwen/Qwen3-30B-A3B
- LoRA adapter：jeeejeee/qwen3-moe-text2sql-spider

## 错误现象
调用栈如下：
FusedMoEWithLoRA.__init__()
  └─ _inject_lora_into_fused_moe()
       └─ TritonExperts(...)   在 Ascend 下变成 NoneType

## 根因分析
FusedMoEWithLoRA 的默认 LoRA 注入逻辑对 GPU/Triton fused MoE 路径有隐含依赖。
_inject_lora_into_fused_moe() 内部会构造 TritonExperts、MarlinExperts 等 GPU 风格对象。
在昇腾环境下，select_gemm_impl() 返回 None，随后调用这个 None 对象触发 TypeError。
这不是算子精度问题，是平台执行路径假设不一致。

## 修复方案
在下游 vllm-ascend 做 monkey patch，不修改上游 vllm。
覆盖三个方法：__init__、_inject_lora_into_fused_moe、forward。

关键策略：
1. _inject_lora_into_fused_moe 直接返回，跳过 select_gemm_impl 调用
2. forward 改走 Ascend slow path，手工完成完整计算流程
3. 上游 vllm 保持不变

## 验证结果
在 Ascend 910B × 2，TP=2 场景下，两卡输出一致，断言通过。
MANUAL_TP2_ASSERTION_PASSED

## 修复性质
- 仅修改 vllm-ascend，上游 vllm 未动
- 影响范围仅 Ascend 平台
- 当前为 slow path workaround，功能正确，性能未优化
