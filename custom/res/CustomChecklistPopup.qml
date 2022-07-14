/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick          2.11
import QtQuick.Controls 2.4
import QtQuick.Dialogs  1.3

import QGroundControl           1.0
import QGroundControl.Vehicle   1.0
import QGroundControl.Controls  1.0

/// Popup container for preflight checklists
QGCPopupDialog {
    id:         _root
    title:      qsTr("Pre-Flight Checklist")
    buttons:    StandardButton.Close
    property bool   destroyOnClose:         false

    property var    _activeVehicle:     QGroundControl.multiVehicleManager.activeVehicle        
                                                                                                //true                                                                 //Non-zero
    property bool   _useChecklist:      QGroundControl.settingsManager.appSettings.useChecklist.rawValue && QGroundControl.corePlugin.options.preFlightChecklistUrl.toString().length
                                            //true                                                                    //true
    property bool   _enforceChecklist:  _useChecklist && QGroundControl.settingsManager.appSettings.enforceChecklist.rawValue
                                           //true                              
    property bool   _checklistComplete: _activeVehicle && (_activeVehicle.checkListState === Vehicle.CheckListPassed)
                                            //If there is an active vehicle, _vehicleArmed is set to _activeVehicle.armed value, otherwise its just false
    property bool   _vehicleArmed:      _activeVehicle ? _activeVehicle.armed : false // true here prevents pop up from showing during shutdown

    

    on_ActiveVehicleChanged: _showPreFlightChecklistIfNeeded()


    Connections {
        target:                             mainWindow

        onShowPreFlightChecklistIfNeeded:   _root._showPreFlightChecklistIfNeeded()
        onDisplayPreFlightChecklist:        _root._displayPreFlightChecklist()
    }


    function _showPreFlightChecklistIfNeeded() {
        console.log("Popup: CHECKLIST STATUS: ", _activeVehicle.checkListState)
        //if theres an active vehicle, vehicle is not armed, checklist is not complete, and checklist is enforced, restart the timer
        if (_activeVehicle && !_vehicleArmed && !_checklistComplete && _enforceChecklist) {
            console.log("Popup: Restart timer")
            popupTimer.restart()
        }
    }

    function _displayPreFlightChecklist() {
        console.log("Popup: DISPLAY CHECKLIST")
        _root.open()
    }


    Timer {
        id:             popupTimer
        interval:       1000
        repeat:         false
        onTriggered: {
            //if checklist not complete, open it, otherwise close it
            if (!_checklistComplete) {
                console.log("Popup: OPEN ROOT")
                _root.open()
            } else {
                _root.close()
            }
        }
    }




    Loader {
        id:     checkList
        //                                      "qrc:/qml/PreFlightCheckList.qml" i.e. CustomPreFlightCheckList.qml
        source: QGroundControl.corePlugin.options.preFlightChecklistUrl
    }



    property alias checkListItem: checkList.item



    Connections {
        target: checkList.item
        onAllChecksPassedChanged: {
            if (target.allChecksPassed) {
                popupTimer.restart()
            }
        }
    }
}
