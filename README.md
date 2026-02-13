# pdfhenshu

`pdf_as` 風の「軽量・必要十分」なPDF編集ツールを C 言語で作るための、
実装開始用プロトタイプです。

## 現在の方針

- 回転・抽出・結合を中心にする
- 回転は `90/180/270` のみ（角度補正は対象外）
- 将来のプレビュー機能追加を見据えてレイヤ分離する
- DLL 同梱でインストール不要（Portable配布）

## できること（現時点）

- ポータブル設定の読み込み（`runtime/pdfhenshu.ini`）
- コマンドの受け取りと検証
- qpdf実行コマンドの組み立て表示（実実行は次フェーズ）

```bash
pdfhenshu --show-config
pdfhenshu rotate input.pdf out.pdf 3-7 90
pdfhenshu extract input.pdf out.pdf 5,18
pdfhenshu merge out.pdf a.pdf b.pdf c.pdf
```

## ディレクトリ

- `src/`: Cソース
- `include/`: ヘッダ
- `runtime/`: ポータブル設定
- `docs/`: 設計・運用ドキュメント
- `tools/`: 配布補助スクリプト（`doctor.bat` で配置チェック可）

## ビルド

- VSCode利用時は `.editorconfig` により文字コード/改行を統一しています（UTF-8/LF）。


```bash
cmake -S . -B build
cmake --build build
./build-ninja/pdfhenshu --show-config
```

またはプリセット:

```bash
cmake --preset default
cmake --build --preset default
./build-ninja/pdfhenshu --show-config
```


## VSCodeでの実行（Windows）

- まず `F5` の「プロセスにアタッチ」ではなく、`launch` 構成で起動してください。
- Windows では `Windows: Run pdfhenshu (--show-config)` を選んでください。
- 手順は `docs/VSCODE_WINDOWS.md` を参照してください。
- このリポジトリには `.vscode/tasks.json` / `.vscode/launch.json` / `.vscode/settings.json` を同梱しています。

## Portable（Windows）

- 依存 EXE/DLL を同梱して配布
- 詳細は `docs/PORTABLE_WINDOWS.md`

## 次フェーズ

1. qpdfを実際に呼び出してPDFを生成
2. MuPDF/Popplerでサムネイルプレビュー実装
3. GTKでページ一覧UI（選択・並び替え・回転）
