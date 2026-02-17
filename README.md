# 嵌入式回声消除库 (libaec)

纯C实现的轻量级回声消除器，基于NLMS（归一化最小均方）自适应滤波算法。

## 特性

- 无第三方依赖
- 内存占用小
- 适用于嵌入式系统
- 实时处理
- 专为16K 16bit单声道优化

## 编译

```bash
make
```

## 运行示例

```bash
./example
```

## API使用

```c
#include "aec.h"

// 初始化（滤波器长度256，步长0.3）
aec_t *aec = aec_init(256, 0.3f);

// 处理16bit采样点
int16_t output = aec_process(aec, ref_sample, mic_sample);

// 销毁
aec_destroy(aec);
```

## 参数说明

- **采样率**: 16000 Hz
- **位深**: 16 bit
- **声道**: 单声道
- **filter_len**: 滤波器长度，建议128-512
- **mu**: 步长因子，建议0.1-0.5
- **ref_sample**: 参考信号（远端播放的16bit采样点）
- **mic_sample**: 麦克风信号（包含回声的16bit采样点）

## 内存占用

约 `filter_len * 8 + 40` 字节（filter_len=256时约2KB）
