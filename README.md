# 注意UDP发送的数据必须用QByteArray形式才行


```
if (!image.loadFromData(QByteArray::fromHex(data.toUtf8()), "JPEG"))

```