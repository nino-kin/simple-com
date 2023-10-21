# Memo

## Class diagram

- [x] Need to make the whole of Class diagram.

## Self study

- [UDP Server-Client implementation in C++](https://www.geeksforgeeks.org/udp-server-client-implementation-c/)

- [【C++】UDP通信を実装する（Windows/Linux環境）](https://shizenkarasuzon.hatenablog.com/entry/2020/06/25/150229)

- [socket connect() vs bind()](https://stackoverflow.com/questions/27014955/socket-connect-vs-bind)

## File structure

ソケット通信と送受信時のログ機能を兼ね備えたC++ライブラリを作成するために、以下に示す主要な機能を含む10個以上のファイル（モジュール）に分割して実装できます。これには、クラス定義、API関数、ヘッダーファイル、および詳細な解説が含まれます。

1. **Socket.hpp / Socket.cpp**:
   - ソケット通信を抽象化するためのSocketクラスの定義と実装
   - ソケットの作成、接続、データ送信、データ受信などの基本的な操作

2. **Logger.hpp / Logger.cpp**:
   - ログ機能を提供するLoggerクラスの定義と実装
   - ログファイルへの書き込み、ログレベル設定、ログフォーマットのカスタマイズ

3. **SocketLogger.hpp / SocketLogger.cpp**:
   - SocketLoggerクラスの定義と実装
   - ソケット通信とログ機能を統合し、データ送受信時にログを記録する機能を提供

4. **SocketException.hpp / SocketException.cpp**:
   - 例外処理用のSocketExceptionクラスの定義と実装
   - ソケット操作中に発生するエラーをハンドリング

5. **SocketOptions.hpp / SocketOptions.cpp**:
   - ソケットオプションを設定するためのSocketOptionsクラスの定義と実装
   - タイムアウト、バッファサイズなどのオプションをカスタマイズ

6. **SocketUtils.hpp / SocketUtils.cpp**:
   - ソケット通信に関連するユーティリティ関数の定義と実装
   - IPアドレスの解決、ポート番号の変換、ネットワークバイトオーダーへの変換など

7. **Packet.hpp / Packet.cpp**:
   - データパケットの定義と実装
   - データのシリアル化とデシリアル化、データパケットのヘッダー情報

8. **SocketEvent.hpp / SocketEvent.cpp**:
   - ソケットイベントを扱うSocketEventクラスの定義と実装
   - ソケットイベントのトリガーとハンドリング

9. **SocketListener.hpp / SocketListener.cpp**:
   - ソケット接続待機を処理するSocketListenerクラスの定義と実装
   - クライアントからの接続要求を待ち受け、新しいソケットを作成

10. **Main.cpp**:
    - サンプルプログラムまたはテスト用のエントリーポイント

これらのファイルとモジュールは、ソケット通信とログ機能を統合したC++ライブラリを実装するための基本的な要素です。各ファイルには詳細なコメントとドキュメンテーションを含め、使いやすく、他の開発者が理解しやすいように注意してください。ライブラリを実際に使う場合には、SocketクラスとLoggerクラスを組み合わせて、ソケット通信時にログを記録できるようになります。

## CMake

Activate debug

```console
$ cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug && cmake --build build && cd build && ctest -VV -O $TEST_LOG_FILENAME
```
