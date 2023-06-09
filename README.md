# Open-TTTV
WISS2022で発表したOpen-TTTVの作り方についての記事です
<br>
https://research.miyashita.com/papers/D265
![maxresdefault](https://github.com/MiyashitaLab/Open-TTTV/assets/75302406/e3a12b44-d127-4a2f-b1e1-398a7da54043)

## 必要なもの
・[本リポジトリ内のSTLファイル](https://github.com/MiyashitaLab/Open-TTTV/tree/main/STL)<br>
　ファイルの最後に数字がある場合はその数印刷してください<br>
　Open-TTTVを傾ける台は噴霧対象に応じて使い分けてください<br>
・[無印良品　ポリエチレン小分けボトル　スプレータイプ　15ml](https://www.muji.com/jp/ja/store/cmdty/detail/4550344579145)　190円 ×9<br>
・[タカハ機工　CB12500045 プッシュソレノイド DC6V仕様](https://www.monotaro.com/p/4063/8168/)　2590円<br>
・[FEETECH FT1117M ミニPWMサーボ](https://ssci.to/7118)　957円<br>
・[スイッチングＡＣアダプター9V2A　AD-A90P200](https://akizukidenshi.com/catalog/g/gM-08309/)　1100円<br>
・[M5Stack用ME3116AM6G搭載 5V 降圧コンバータユニット](https://ssci.to/7481)　561円<br>
・[M5Stack BAVG2ソケット](https://ssci.to/7234)　429円<br>
・[M5Stack用拡張ハブユニット [U006]](https://ssci.to/5696)　517円<br>
・[Solenoid UNIT](https://ssci.to/8517)　660円<br>
・[ATOM Lite](https://ssci.to/6262)　1342円<br>
・[GROVE - サーボ用2分岐ケーブル (5本セット)](https://ssci.to/1250)　847円<br>
・[SARASA](https://www.zebra.co.jp/pro/detail/sarasa-clip/?tab=lineup_sarasa-clip_05) 110円×9<br>
・[2.1ｍｍ ΦＤＣ分岐ケーブル](https://akizukidenshi.com/catalog/g/gC-06723/)　350円<br>
・[皿頭小ねじ(ステンレス)](https://www.monotaro.com/p/0550/8465/)　M3×30　1つ<br>
・[皿頭小ねじ(ステンレス)](https://www.monotaro.com/p/0550/8535/)　M4×10　4つ<br>
・[皿頭小ねじ(ステンレス)](https://www.monotaro.com/p/0550/8754/)　M5×15　4つ<br>
・[六角ナット　2種(ステンレス)](https://www.monotaro.com/p/4221/7585/)　M5　4つ<br>
※サイズ・規格等が同じであれば上記リンク以外のものでも構いません
※価格は2023年5月28日時点での価格です。

## 作り方

https://github.com/MiyashitaLab/Open-TTTV/assets/75302406/29ad6028-4944-4c81-b780-6740f61415f1

より詳しい作り方は[こちらのページ](https://github.com/MiyashitaLab/Open-TTTV/blob/main/HowToMake.md)を参照してください<br>
※必要に応じてケーブルの処理、接着等を行ってください<br>
※スプレーボトル内部のばねをSARASAのばねと交換してください<br>

## 内部の組み立て
内部の組み立ては以下の図を参照してください<br>
![Open-TTTV2](https://github.com/MiyashitaLab/Open-TTTV/assets/75302406/9035a545-445b-42c6-b418-01d8354de236)

## 使用方法
①ATOM LiteにCode内のプログラムを書き込む<br>
　※コンパイルには"M5Atom"、"ESP32Servo"のライブラリが必要です<br>
　※data内のファイルはArduinoで書き込みするだけでは転送されず、別途SPIFFSアップローダを使って転送する必要があります<br>
 　　詳細は[こちらのページ](https://www.mgo-tec.com/blog-entry-spiffs-uploader-plugin-arduino-esp32.html)を参考にしてください<br>
②スマホからATOM Liteに接続する<br>
　設定画面からWi-fiの接続先を検索し、Open-TTTVと接続します。初期パスワードは"opentttv"です。<br>
③ブラウザでIPアドレスを入力しページを開く<br>
　任意のブラウザを立ち上げ、IPアドレスを入力して下さい<br>
④任意に味を調整しSENDボタンを押す<br>
　任意の画像を選択、味を調整し、画面下部にあるTransformボタンを押すことでOpen-TTTVから味が出力されます。<br>
 ![DSC06923](https://github.com/MiyashitaLab/Open-TTTV/assets/75302406/553fa310-dc54-4407-ae7d-a8a765970340)

## License

The MIT License(MIT)

Copyright (c) [2023] [MiyashitaLab]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
