# VSCodeでの実行手順（Windows）

## まず結論

画像の状態は「プロセスへアタッチ」画面なので、今の使い方だと実行しづらいです。
このプロジェクトは **Launch（起動）構成** で動かしてください。

## 前提で必要なもの

- VSCode
- 拡張機能
  - C/C++ (`ms-vscode.cpptools`)
  - CMake Tools (`ms-vscode.cmake-tools`)
- Cコンパイラ（どちらか）
  - MinGW-w64 (gcc/g++)
  - Visual Studio Build Tools (cl)
- CMake
- （実PDF処理をする次フェーズで）`qpdf.exe` と `mutool.exe` + 依存DLL

## このリポジトリに含めたVSCode設定

- `.vscode/tasks.json`
  - `cmake-configure`
  - `cmake-build`
- `.vscode/launch.json`
  - `Run pdfhenshu (--show-config)`
  - `Run pdfhenshu (rotate sample)`

## 実行手順

1. VSCodeでフォルダを開く
2. ターミナルで `cmake -S . -B build` が通ることを確認
3. `F5` を押す
4. 実行構成で `Run pdfhenshu (--show-config)` を選ぶ

## よくある詰まりポイント

- `config.h` が見つからない
  - CMakeでビルドしているか確認（`target_include_directories`で`include/`を参照）
- `program does not exist`
  - まだ `build/pdfhenshu(.exe)` が作られていない。先にビルドする
- Attach画面が出る
  - `launch.json` の `request` が `attach` ではなく `launch` か確認
- `C4067` が `config.h` 1行目で出る
  - 例: `#ifndef PDFHE#ifndef ...` のように同じ行へ混ざっている状態です。
  - `config.h` を開き、1行目を `#ifndef PDFHENSHU_CONFIG_H` のみへ修正してください。
  - 保存時エンコーディングを **UTF-8**、改行を **LF** にしてください（`.editorconfig` を追加済み）。
- `C4996 fopen may be unsafe`
  - このリポジトリ側で `fopen_s` 対応と `_CRT_SECURE_NO_WARNINGS` 定義を追加済みです。

## ファイル構成はこれでOK？

はい、現在の構成で問題ありません。最低限は下記です。

- `CMakeLists.txt`
- `src/`（`main.c`, `config.c`）
- `include/`（`config.h`）
- `runtime/`（`pdfhenshu.ini`）

追加であると便利なもの：

- `.vscode/`（今回追加）
- `docs/`（運用手順）
- `tools/`（配布補助スクリプト）
