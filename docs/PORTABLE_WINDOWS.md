# Portable Windows 運用（インストール不要）

このプロジェクトは DLL 同梱で、インストールせずに実行する前提です。

## 配布フォルダ例

```text
pdfhenshu/
  pdfhenshu.exe
  runtime/
    pdfhenshu.ini
    bin/
      qpdf.exe
      mutool.exe
    dll/
      *.dll
```

## ポイント

- `pdfhenshu.exe` と同階層の `runtime/` を読む
- 依存 DLL は `runtime/dll` に同梱
- `pdfhenshu.ini` で実行ファイルパスを固定管理
- 角度補正は対象外、回転は `90/180/270` のみ

## 起動時のDLL探索

Windowsでは通常、実行ファイル配置フォルダのDLLが優先探索されます。
より厳密にする場合、`SetDefaultDllDirectories` と `AddDllDirectory` を
利用して `runtime/dll` を明示登録してください。
