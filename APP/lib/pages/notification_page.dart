import 'dart:async';
import 'dart:convert';
import 'dart:ffi';
// import 'dart:ffi';
import 'dart:math';
import 'dart:typed_data';
import 'dart:developer';
import 'package:intl/intl.dart';

import 'package:flutter/material.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import 'package:notification_listener_service/notification_event.dart';
import 'package:notification_listener_service/notification_listener_service.dart';
import 'package:pbl4/utils/extra.dart';
import 'package:pbl4/utils/functions_enum.dart';
import 'package:pbl4/utils/get_ble_charecteristic.dart';
import 'package:pbl4/utils/snackbar.dart';

class NotificationPage extends StatefulWidget {
  final BluetoothDevice device;
  const NotificationPage({Key? key, required this.device}) : super(key: key);

  @override
  State<NotificationPage> createState() => _NotificationPageState();
}

class _NotificationPageState extends State<NotificationPage> {
  StreamSubscription<ServiceNotificationEvent>? _subscription;
  List<ServiceNotificationEvent> events = [];
  int? _rssi;
  int? _mtuSize;
  BluetoothConnectionState _connectionState =
      BluetoothConnectionState.disconnected;
  List<BluetoothService> _services = [];
  bool _isDiscoveringServices = false;
  bool _isConnecting = false;
  bool _isDisconnecting = false;
  int? _steps;

  late StreamSubscription<BluetoothConnectionState>
      _connectionStateSubscription;
  late StreamSubscription<bool> _isConnectingSubscription;
  late StreamSubscription<bool> _isDisconnectingSubscription;
  late StreamSubscription<int> _mtuSubscription;
  BluetoothDevice get device => widget.device;
  late int now;
  Timer? timer;

  Future onDiscoverServicesPressed() async {
    if (mounted) {
      setState(() {
        _isDiscoveringServices = true;
      });
    }
    try {
      _services = await widget.device.discoverServices();
      Snackbar.show(ABC.c, "Discover Services: Success", success: true);
    } catch (e) {
      Snackbar.show(ABC.c, prettyException("Discover Services Error:", e),
          success: false);
    }
    if (mounted) {
      setState(() {
        _isDiscoveringServices = false;
      });
    }
  }

  Future onTimeWrite() async {
    BluetoothCharacteristic c = getBluetoothCharacteristic(
        widget.device.remoteId, ServiceEnum.timeSync, Characteristic.timeSync);
    // List<int> data = utf8.encode(now.toInt().toString()).toList();
    Uint8List int32BigEndianBytes(int value) =>
        Uint8List(4)..buffer.asByteData().setUint32(0, value, Endian.little);
    Uint8List data = int32BigEndianBytes(now);

    try {
      await c.write(data, withoutResponse: false);
      Snackbar.show(ABC.c, "Write: Success", success: true);
      if (c.properties.read) {
        await c.read();
      }
    } catch (e) {
      Snackbar.show(ABC.c, prettyException("Write Error:", e), success: false);
    }
  }

  Future<void> splitWrite(List<int> value, {int timeout = 15}) async {
    BluetoothCharacteristic c = getBluetoothCharacteristic(
        widget.device.remoteId, ServiceEnum.timeSync, Characteristic.timeSync);
    int chunk = device.mtuNow - 3; // 3 bytes ble overhead
    for (int i = 0; i < value.length; i += chunk) {
      List<int> subvalue = value.sublist(i, min(i + chunk, value.length));
      await c.write(subvalue, withoutResponse: false, timeout: timeout);
    }
  }

  Future onWriteNotificationText(String notify) async {
    var text = notify;
    if (text.length > 240) {
      final trimText = text.split('').getRange(0, 230).toList();
      trimText.add('...');
      text = trimText.join('');
    }
    BluetoothCharacteristic textUUID = getBluetoothCharacteristic(
        widget.device.remoteId,
        ServiceEnum.notification,
        Characteristic.notificationText);

    final dataText = utf8.encode(text).map((e) => e.toRadixString(16)).toList();
    dataText.add('00');
    final data = dataText.map((e) => int.parse(e, radix: 16)).toList();
    try {
      await textUUID.write(data, withoutResponse: false);
      Snackbar.show(ABC.c, "Write: Success", success: true);
    } catch (e) {
      Snackbar.show(ABC.c, prettyException("Write Error:", e), success: false);
    }
  }

  Future onWriteNotificationTitle(String title) async {
    BluetoothCharacteristic titleUUID = getBluetoothCharacteristic(
        widget.device.remoteId,
        ServiceEnum.notification,
        Characteristic.notificationTitle);
    final dataTitle =
        utf8.encode(title).map((e) => e.toRadixString(16)).toList();
    dataTitle.add('00');
    print(dataTitle);
    final data = dataTitle.map((e) => int.parse(e, radix: 16)).toList();
    try {
      await titleUUID.write(data,
          withoutResponse: titleUUID.properties.writeWithoutResponse);
      Snackbar.show(ABC.c, "Write: Success", success: true);
      // if (c.properties.read) {
      //   await c.read();
      // }
    } catch (e) {
      Snackbar.show(ABC.c, prettyException("Write Error:", e), success: false);
    }
  }

  Future onReadPressed() async {
    BluetoothCharacteristic c = getBluetoothCharacteristic(
        widget.device.remoteId,
        ServiceEnum.stepCounter,
        Characteristic.stepCounter);
    try {
      var steps = await c.read();
      print(String.fromCharCodes(steps));
      var list = Uint16List(steps.length);
      for (var i = 0; i < steps.length; i++) {
        list[i] = steps[i];
      }
      final data = list.buffer.asByteData();
      setState(() {
        _steps = data.getUint16(0, Endian.little);
        print(data.getUint16(0, Endian.little));
      });

      Snackbar.show(ABC.c, "Read: Success", success: true);
    } catch (e) {
      Snackbar.show(ABC.c, prettyException("Read Error:", e), success: false);
    }
  }

  Future onRequestMtuPressed() async {
    try {
      await widget.device.requestMtu(517, predelay: 0);
      Snackbar.show(ABC.c, "Request Mtu: Success", success: true);
    } catch (e) {
      Snackbar.show(ABC.c, prettyException("Change Mtu Error:", e),
          success: false);
    }
  }

  Future onDisconnectPressed() async {
    try {
      await widget.device.disconnectAndUpdateStream();
      Snackbar.show(ABC.c, "Disconnect: Success", success: true);
    } catch (e) {
      Snackbar.show(ABC.c, prettyException("Disconnect Error:", e),
          success: false);
    }
  }

  @override
  void initState() {
    super.initState();
    _connectionStateSubscription =
        widget.device.connectionState.listen((state) async {
      _connectionState = state;
      if (state == BluetoothConnectionState.connected) {
        _services = []; // must rediscover services
        onDiscoverServicesPressed();
      }
      if (state == BluetoothConnectionState.connected && _rssi == null) {
        _rssi = await widget.device.readRssi();
      }
      if (state == BluetoothConnectionState.disconnected) {
        print('disconnected');
        setState(() {
          _isDisconnecting = true;
        });
      }
      if (mounted) {
        setState(() {});
      }
    });

    _mtuSubscription = widget.device.mtu.listen((value) {
      _mtuSize = value;
      print("MTU: $value");
      if (mounted) {
        setState(() {});
      }
    });

    _isConnectingSubscription = widget.device.isConnecting.listen((value) {
      _isConnecting = value;
      if (mounted) {
        setState(() {});
      }
    });

    _isDisconnectingSubscription =
        widget.device.isDisconnecting.listen((value) {
      _isDisconnecting = value;
      if (mounted) {
        setState(() {});
      }
    });

    timer = Timer.periodic(Duration(seconds: 3), (Timer t) => onReadPressed());
  }

  @override
  void dispose() {
    timer?.cancel();
    super.dispose();
  }

  bool checkMessengerNotification(ServiceNotificationEvent event) {
    switch (event.title) {
      case "Dymki czatu są aktywne":
        return false;
      case "Messenger wyświetla się nad innymi":
        return false;
      default:
        return true;
    }
  }

  int getTime(DateTime time) {
    var dateTime =
        DateFormat("yyyy-MM-dd HH:mm:ss").parse(time.toString(), true);
    var dateLocal = dateTime.toLocal();
    return dateLocal.millisecondsSinceEpoch ~/ 1000;
  }

  @override
  Widget build(BuildContext context) {
    now = getTime(DateTime.now());
    return Builder(builder: (context) {
      if (_isDisconnecting) {
        Navigator.of(context).pop();
        return SizedBox.shrink();
      }
      if (_services.isNotEmpty) {
        if (_steps == null) {
          onRequestMtuPressed();
          onTimeWrite();
          onReadPressed();
        }
        return Scaffold(
          floatingActionButton: FloatingActionButton(
              child: const Text("Disconn"),
              onPressed: () {
                onDisconnectPressed();
              }),
          appBar: AppBar(
            title: const Text('Notification'),
            actions: [
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 8.0),
                child: Text("Steps: ${_steps ?? "-"} "),
              )
            ],
          ),
          body: RefreshIndicator(
            onRefresh: () {
              onTimeWrite();
              return onReadPressed();
            },
            child: Center(
              child: Column(
                children: [
                  SingleChildScrollView(
                    scrollDirection: Axis.horizontal,
                    child: Row(
                      crossAxisAlignment: CrossAxisAlignment.center,
                      children: [
                        TextButton(
                          onPressed: () {
                            setState(() {
                              events.clear();
                            });
                          },
                          child: const Text("Clear notifications"),
                        ),
                        TextButton(
                          onPressed: () async {
                            const snackBar = SnackBar(
                              content: Text('Permission granted'),
                            );
                            final res = await NotificationListenerService
                                .requestPermission();
                            if(res){
                              ScaffoldMessenger.of(context).showSnackBar(snackBar);
                            }
                            // log("Is enabled: $res");
                          },
                          child: const Text("Request Permission"),
                        ),
                        const SizedBox(height: 20.0),
                        TextButton(
                          onPressed: () async {
                            const snackBar = SnackBar(
                              content: Text('Permission granted'),
                            );
                            const snackBarDenigned = SnackBar(
                              content: Text('Permission denigned'),
                            );
                            final bool res = await NotificationListenerService
                                .isPermissionGranted();
                                if(res){
                                  ScaffoldMessenger.of(context).showSnackBar(snackBar);
                                }
                                else{
                                  ScaffoldMessenger.of(context).showSnackBar(snackBarDenigned);
                                }
                            // log("Is enabled: $res");
                          },
                          child: const Text("Check Permission"),
                        ),
                        const SizedBox(height: 20.0),
                        TextButton(
                          
                          onPressed: () {
                            const snackBar = SnackBar(
                              content: Text('Start listening'),
                            );
                            ScaffoldMessenger.of(context).showSnackBar(snackBar);
                            _subscription = NotificationListenerService
                                .notificationsStream
                                .listen((event) {
                              // log("$event");
                              if (event.title != null &&
                                  event.content != null) {
                                if (checkMessengerNotification(event)) {
                                  setState(() {
                                    onWriteNotificationTitle(
                                        event.title ?? "-");
                                    onWriteNotificationText(
                                        event.content ?? "-");
                                    events = [event, ...events];
                                  });
                                }
                              }
                            });
                          },
                          child: const Text("Start Stream"),
                        ),
                        const SizedBox(height: 20.0),
                        TextButton(
                          onPressed: () {
                            const snackBar = SnackBar(
                              content: Text('Stop listening'),
                            );
                            ScaffoldMessenger.of(context).showSnackBar(snackBar);
                            _subscription?.cancel();
                          },
                          child: const Text("Stop Stream"),
                        ),
                      ],
                    ),
                  ),
                  Expanded(
                    child: ListView.builder(
                      shrinkWrap: true,
                      itemCount: events.length,
                      itemBuilder: (_, index) => Padding(
                        padding: const EdgeInsets.only(bottom: 8.0),
                        child: Container(
                          margin: EdgeInsets.symmetric(horizontal: 15),
                          padding: EdgeInsets.symmetric(horizontal: 4),
                          decoration: BoxDecoration(
                            color: Color.fromARGB(255, 243, 207, 244),
                            borderRadius: BorderRadius.circular(30),
                          ),
                          child: ListTile(
                            contentPadding: EdgeInsets.zero,

                            onTap: () async {
                              // try {
                              //   await events[index]
                              //       .sendReply("This is an auto response");
                              // } catch (e) {
                              //   // log(e.toString());
                              // }
                            },
                            // trailing: events[index].hasRemoved!
                            //     ? const Text(
                            //         "Removed",
                            //         style: TextStyle(color: Colors.red),
                            //       )
                            //     : const SizedBox.shrink(),
                            leading: events[index].largeIcon != null
                                ? Image.memory(
                                    events[index].largeIcon!,
                                  )
                                : const SizedBox.shrink(),
                            // events[index].appIcon == null
                            //     ? const SizedBox.shrink()
                            //     : Image.memory(
                            //         events[index].appIcon!,
                            //         width: 35.0,
                            //         height: 35.0,
                            //       ),
                            title: Text(events[index].title ?? "No title"),
                            subtitle: Column(
                              crossAxisAlignment: CrossAxisAlignment.start,
                              children: [
                                Text(
                                  events[index].content ?? "no content",
                                  style: const TextStyle(
                                      fontWeight: FontWeight.bold),
                                ),
                                // events[index].canReply!
                                //     ? const Text(
                                //         "Replied with: This is an auto reply",
                                //         style: TextStyle(color: Colors.purple),
                                //       )
                                //     : const SizedBox.shrink(),
                              ],
                            ),
                            isThreeLine: true,
                          ),
                        ),
                      ),
                    ),
                  )
                ],
              ),
            ),
          ),
        );
      } else {
        return Center(
          child: CircularProgressIndicator(),
        );
      }
    });
  }
}

String loremipsum =
    "Exploring the depths of human curiosity, we journey through the realms of knowledge, weaving tales of inspiration, innovation, and discovery. Each step forward, a testament to our collective intellect, shaping the world with every thought and action.";
