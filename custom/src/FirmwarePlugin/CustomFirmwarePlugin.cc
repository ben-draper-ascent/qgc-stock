/****************************************************************************
 *
 * (c) 2009-2019 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 * @file
 *   @brief Custom Firmware Plugin (PX4)
 *   @author Gus Grubba <gus@auterion.com>
 *
 */

#include "CustomFirmwarePlugin.h"
#include "CustomAutoPilotPlugin.h"

//-----------------------------------------------------------------------------
CustomFirmwarePlugin::CustomFirmwarePlugin(void)
{
    setSupportedModes({
        APMCopterMode(APMCopterMode::STABILIZE,     false),
        APMCopterMode(APMCopterMode::ACRO,          false),
        APMCopterMode(APMCopterMode::ALT_HOLD,      true),
        APMCopterMode(APMCopterMode::AUTO,          true),
        APMCopterMode(APMCopterMode::GUIDED,        true),
        APMCopterMode(APMCopterMode::LOITER,        true),
        APMCopterMode(APMCopterMode::RTL,           true),
        APMCopterMode(APMCopterMode::CIRCLE,        true),
        APMCopterMode(APMCopterMode::LAND,          true),
        APMCopterMode(APMCopterMode::DRIFT,         false),
        APMCopterMode(APMCopterMode::SPORT,         false),
        APMCopterMode(APMCopterMode::FLIP,          false),
        APMCopterMode(APMCopterMode::AUTOTUNE,      false),
        APMCopterMode(APMCopterMode::POS_HOLD,      true),
        APMCopterMode(APMCopterMode::BRAKE,         false),
        APMCopterMode(APMCopterMode::THROW,         false),
        APMCopterMode(APMCopterMode::AVOID_ADSB,    false),
        APMCopterMode(APMCopterMode::GUIDED_NOGPS,  false),
        APMCopterMode(APMCopterMode::SMART_RTL,     false),
        APMCopterMode(APMCopterMode::FLOWHOLD,      false),
        APMCopterMode(APMCopterMode::FOLLOW,        false),
        APMCopterMode(APMCopterMode::ZIGZAG,        false),
        APMCopterMode(APMCopterMode::ZIGZAG,        false),
        APMCopterMode(APMCopterMode::SYSTEMID,      false),
        APMCopterMode(APMCopterMode::AUTOROTATE,    false),
        APMCopterMode(APMCopterMode::AUTO_RTL,      false),
        APMCopterMode(APMCopterMode::TURTLE,        false),
    });
}
//-----------------------------------------------------------------------------
