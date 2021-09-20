# SRAM 2114 4kbit(1024word*4bit) メモリーテストプログラム

## 概要

・新古品として購入した 4kbit(1024word*4bit) SRAM が正常に機能するかチェックする為、書き込み/読み込みテストプログラムを作成した
⇒テスト対象SRAMは NEC uPD2114L および TOSHIBA TC551001CP-85L(4kbit分だけテスト)で実施した

・プログラムは kanpapa氏が作成された arduinoによる 64kbit(8192word*8bit) SRAM の書き込み/読み込みテストプログラムを基に、アドレス長/データ長を変更した
https://kanpapa.com/today/2018/08/arduino-mega-memory-check.html
https://github.com/kanpapa/arduino/blob/master/HM6264TEST

・また今回の検証の為に[秋月電子製 arduino uno互換機 AE-ATMEGA-UNO-R3](https://akizukidenshi.com/catalog/g/gM-15574/)を使った為、ピンアサインの修正も行った

・プログラムはランダムな値を未接続なanalogピンをシード値とした乱数を取得後にSRAMへ書き込み⇒1usウェイト⇒読み込み⇒1usウェイトを行い、書き込んだ値と読み込んだ値が一致すれば成功とする

## 回路図

・uPD2114Lを接続した際は以下の通り

![uPD2114L回路図](https://github.com/wakimizufu/sram_2114_MemoryTest/blob/main/4bit_SRAM_TEST_PROGRAM/4bitSramTest.png)

## 実施レポート

・具体的なテスト実施方法とシリアルデータの見方は [kanpapa氏のBlogに記載されている内容と同様の方法で行った](https://kanpapa.com/today/2018/08/arduino-mega-memory-check.html)

・uPD2114LおよびTC551001CP-85Lで実施した際、全てのアドレスで書き込み値と読み込み値が一致していることを確認した

　⇒それぞれ全アドレスへのチェックを5回繰り返したが問題無いことを確認出来た

## 参考リンク

[4 Kbit S-RWM](http://www.st.rim.or.jp/~nkomatsu/srwm/i2114.html)
