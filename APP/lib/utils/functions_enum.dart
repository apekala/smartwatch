import 'package:flutter_blue_plus/flutter_blue_plus.dart';

enum ServiceEnum {
  notification,
  stepCounter,
  timeSync,
}

enum Characteristic{
  notificationTitle,
  notificationText,
  stepCounter,
  timeSync,
}

extension ServiceExtension on ServiceEnum{
  Guid get serviceUUID{
    switch (this) {
      case ServiceEnum.notification:
        return Guid.fromString("281A2C20-BA6F-4D44-B52F-9C1347EEABDB");
      case ServiceEnum.stepCounter:
        return Guid.fromString('01118473-E39D-479B-ABB5-093493625221');
      case ServiceEnum.timeSync:
        return Guid.fromString("0f7fe290-4bda-4d30-803d-561fd52e18a6");
    }
  }
}

extension CharacteristicExtension on Characteristic{
  Guid get characteristicUUID{
    switch (this) {
      case Characteristic.notificationTitle:
        return Guid.fromString("281A2C21-BA6F-4D44-B52F-9C1347EEABDB");
      case Characteristic.stepCounter:
        return Guid.fromString("01118474-E39D-479B-ABB5-093493625221");
      case Characteristic.timeSync:
        return Guid.fromString("0f7fe291-4bda-4d30-803d-561fd52e18a6");
      case Characteristic.notificationText:
        return Guid.fromString("281A2C22-BA6F-4D44-B52F-9C1347EEABDB");
    }
  }
}