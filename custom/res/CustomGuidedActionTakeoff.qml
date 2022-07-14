/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/
import QGroundControl                       1.0
import QGroundControl.FlightDisplay         1.0
import QGroundControl.MultiVehicleManager   1.0



GuidedToolStripAction {
    property var    _activeVehicle:             QGroundControl.multiVehicleManager.activeVehicle

    text:       _guidedController.takeoffTitle
    iconSource: "/res/takeoff.svg"
    visible:    _guidedController.showTakeoff || !_guidedController.showLand
    enabled:    _guidedController.showTakeoff && _activeVehicle
    actionID:   _guidedController.actionTakeoff
}
