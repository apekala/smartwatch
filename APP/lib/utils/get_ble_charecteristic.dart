import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import 'package:pbl4/utils/functions_enum.dart';

BluetoothCharacteristic getBluetoothCharacteristic(
    DeviceIdentifier id, ServiceEnum service, Characteristic characteristic) {
  return BluetoothCharacteristic(
      remoteId: id,
      serviceUuid: service.serviceUUID,
      characteristicUuid: characteristic.characteristicUUID);
}
