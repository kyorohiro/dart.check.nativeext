// Copyright (c) 2012, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

library libhello;

import 'dart-ext:hello';
import 'dart:isolate';

// The simplest way to call native code: top-level functions.
//int systemRand() native "SystemRand";
//int noScopeSystemRand() native "NoScopeSystemRand";
int test(int seed) native "test";

class Testas {
  SendPort _port;
  Testas() {
    _port = _newTestas();
  }

  a() {
    RawReceivePort replyPort = new RawReceivePort();
     print("dart :: send");
    replyPort.handler = (result){
      print("dart :: handler");
//      replyPort.close();
      print("dart :: ${result}");
    };
    _port.send([replyPort.sendPort]);

  }

  SendPort _newTestas() native "testas";
}
