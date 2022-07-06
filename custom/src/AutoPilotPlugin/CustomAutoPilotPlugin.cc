/****************************************************************************
 *
 * (c) 2009-2019 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 * @file
 *   @brief Custom Autopilot Plugin
 *   @author Gus Grubba <gus@auterion.com>
 */

#include "CustomAutoPilotPlugin.h"

#include "QGCApplication.h"
#include "QGCCorePlugin.h"
#include "APMSpiritComponent.h"

#include "APMAutoPilotPlugin.h"
#include "UAS.h"
#include "APMParameterMetaData.h"
#include "APMFirmwarePlugin.h"
#include "ArduCopterFirmwarePlugin.h"
#include "ArduRoverFirmwarePlugin.h"
#include "VehicleComponent.h"
#include "APMAirframeComponent.h"
#include "APMFlightModesComponent.h"
#include "APMRadioComponent.h"
#include "APMSafetyComponent.h"
#include "APMTuningComponent.h"
#include "APMSensorsComponent.h"
#include "APMPowerComponent.h"
#include "APMMotorComponent.h"
#include "APMCameraComponent.h"
#include "APMLightsComponent.h"
#include "APMSubFrameComponent.h"
#include "APMFollowComponent.h"
#include "ESP8266Component.h"
#include "APMHeliComponent.h"
#include "ParameterManager.h"

CustomAutoPilotPlugin::CustomAutoPilotPlugin(Vehicle* vehicle, QObject* parent)
    : APMAutoPilotPlugin(vehicle, parent)
{
    // Whenever we go on/out of advanced mode the available list of settings pages will change
    connect(qgcApp()->toolbox()->corePlugin(), &QGCCorePlugin::showAdvancedUIChanged, this, &CustomAutoPilotPlugin::_advancedChanged);
}

// This signals that when Advanced Mode changes the list of Vehicle Settings page also changed
void CustomAutoPilotPlugin::_advancedChanged(bool)
{
    _components.clear();
    emit vehicleComponentsChanged();
}

// This allows us to hide most Vehicle Setup pages unless we are in Advanced Mmode
const QVariantList& CustomAutoPilotPlugin::vehicleComponents()
{
    if (_components.count() == 0 && !_incorrectParameterVersion) {
        if (_vehicle->parameterManager()->parametersReady()) {
                
            _spiritComponent = new APMSpiritComponent(_vehicle, this);
            _spiritComponent->setupTriggerSignals();
            _components.append(QVariant::fromValue((VehicleComponent*)_spiritComponent));

            _safetyComponent = new APMSafetyComponent(_vehicle, this);
            _safetyComponent->setupTriggerSignals();
            _components.append(QVariant::fromValue(reinterpret_cast<VehicleComponent*>(_safetyComponent)));

            _sensorsComponent = new APMSensorsComponent(_vehicle, this);
            _sensorsComponent->setupTriggerSignals();
            _components.append(QVariant::fromValue((VehicleComponent*)_sensorsComponent));
            
        } 
        else {
            qWarning() << "Call to vehicleCompenents prior to parametersReady";
        }
    }

    return _components;
}


QString CustomAutoPilotPlugin::prerequisiteSetup(VehicleComponent* component) const
{
    bool requiresAirframeCheck = false;

    if (qobject_cast<const APMSpiritComponent*>(component)) {
        requiresAirframeCheck = true;
    } else if (qobject_cast<const APMSafetyComponent*>(component)) {
        requiresAirframeCheck = true;
    } else if (qobject_cast<const APMSensorsComponent*>(component)) {
        requiresAirframeCheck = true;
    }

    if (requiresAirframeCheck) {
        if (_airframeComponent && !_airframeComponent->setupComplete()) {
            return _airframeComponent->name();
        }
    }

    return QString();
}