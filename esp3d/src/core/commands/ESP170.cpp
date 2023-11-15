/*
 ESP122.cpp - ESP3D command class

 Copyright (c) 2014 Luc Lebosse. All rights reserved.

 This code is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with This code; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "../../include/esp3d_config.h"
#if defined(CAMERA_DEVICE)
#include "../../modules/authentication/authentication_service.h"
#include "../../modules/camera/camera.h"
#include "../esp3d_commands.h"
#include "../esp3d_settings.h"
#include "esp_camera.h"

#define COMMAND_ID 170
// Set Camera command value / list all values in JSON/plain
//[ESP170]<plain><label=value> pwd=<admin password>
// label can be:
// light/framesize/quality/contrast/brightness/saturation/gainceiling/colorbar
//              /awb/agc/aec/hmirror/vflip/awb_gain/agc_gain/aec_value/aec2/cw/bpc/wpc
//              /raw_gma/lenc/special_effect/wb_mode/ae_level
void ESP3DCommands::ESP170(int cmd_params_pos, ESP3DMessage* msg) {
  const char* camcmd = [] = {
    "framesize",
    "quality",
    "contrast",
    "brightness",
    "saturation",
    "sharpness",
    "special_effect",
    "wb_mode",
    "awb",
    "awb_gain",
    "aec",
    "aec2",
    "ae_level",
    "aec_value",
    "agc",
    "agc_gain",
    "gainceiling",
    "bpc",
    "wpc",
    "raw_gma",
    "lenc",
    "vflip",
    "hmirror",
    "dcw",
    "colorbar",
#if CAM_LED_PIN != -1
    "light",
#endif  // CAM_LED_PIN
  };
  ESP3DClientType target = msg->origin;
  ESP3DRequest requestId = msg->request_id;
  msg->target = target;
  msg->origin = ESP3DClientType::command;
  bool json = hasTag(msg, cmd_params_pos, "json");
  std::string tmpstr;
#if AUTHENTICATION_FEATURE
  if (msg->authentication_level == ESP3DAuthenticationLevel::guest) {
    dispatchAuthenticationError(msg, COMMAND_ID, json);
    return;
  }
#endif  // AUTHENTICATION_FEATURE
  if (!esp3d_camera.started()) {
    hasError = true;
    error_msg = "No camera initialized";
    esp3d_log_e("%s", error_msg.c_str());
  } else {
    tmpstr = get_clean_param(msg, cmd_params_pos);
    sensor_t* s = esp_camera_sensor_get();
    if (s == nullptr) {
      hasError = true;
      error_msg = "No camera settings available";
      esp3d_log_e("%s", error_msg.c_str());
    } else {
      if (tmpstr.length() == 0) {
        if (json) {
          tmpstr = "{\"cmd\":\"170\",\"status\":\"ok\",\"data\":[";

        } else {
          tmpstr = "Camera:\n";
        }
        msg->type = ESP3DMessageType::head;
        if (!dispatch(msg, tmpstr.c_str())) {
          esp3d_log_e("Error sending response to clients");
          return;
        }
        // now send all settings one by one
        //  framesize
        if (!dispatchIdValue(json, "framesize",
                             String(status.framesize).c_str(), target,
                             requestId, true)) {
          return;
        }

        // quality
        if (!dispatchIdValue(json, "quality", String(status.quality).c_str(),
                             target, requestId)) {
          return;
        }

        // brightness
        if (!dispatchIdValue(json, "brightness",
                             String(status.brightness).c_str(), target,
                             requestId)) {
          return;
        }

        // contrast
        if (!dispatchIdValue(json, "contrast", String(status.contrast).c_str(),
                             target, requestId)) {
          return;
        }

        // saturation
        if (!dispatchIdValue(json, "saturation",
                             String(status.saturation).c_str(), target,
                             requestId)) {
          return;

          // sharpness
          if (!dispatchIdValue(json, "sharpness",
                               String(status.sharpness).c_str(), target,
                               requestId)) {
            return;
          }

          // special_effect
          if (!dispatchIdValue(json, "special_effect",
                               String(status.special_effect).c_str(), target,
                               requestId)) {
            return;
          }

          // wb_mode
          if (!dispatchIdValue(json, "wb_mode", String(status.wb_mode).c_str(),
                               target, requestId)) {
            return;
          }

          // awb
          if (!dispatchIdValue(json, "awb", String(status.awb).c_str(), target,
                               requestId)) {
            return;
          }

          // awb_gain
          if (!dispatchIdValue(json, "awb_gain",
                               String(status.awb_gain).c_str(), target,
                               requestId)) {
            return;
          }

          // aec
          if (!dispatchIdValue(json, "aec", String(status.aec).c_str(), target,
                               requestId)) {
            return;
          }
          // aec2
          if (!dispatchIdValue(json, "aec2", String(status.aec2).c_str(),
                               target, requestId)) {
            return;
          }
          // ae_level
          if (!dispatchIdValue(json, "ae_level",
                               String(status.ae_level).c_str(), target,
                               requestId)) {
            return;
          }
          // aec_value
          if (!dispatchIdValue(json, "aec_value",
                               String(status.aec_value).c_str(), target,
                               requestId)) {
            return;
          }
          // agc
          if (!dispatchIdValue(json, "agc", String(status.agc).c_str(), target,
                               requestId)) {
            return;
          }
          // agc_gain
          if (!dispatchIdValue(json, "agc_gain",
                               String(status.agc_gain).c_str(), target,
                               requestId)) {
            return;
          }
          // gainceiling
          if (!dispatchIdValue(json, "gainceiling",
                               String(status.gainceiling).c_str(), target,
                               requestId)) {
            return;
          }
          // bpc
          if (!dispatchIdValue(json, "bpc", String(status.bpc).c_str(), target,
                               requestId)) {
            return;
          }
          // wpc
          if (!dispatchIdValue(json, "wpc", String(status.wpc).c_str(), target,
                               requestId)) {
            return;
          }
          // raw_gma
          if (!dispatchIdValue(json, "raw_gma", String(status.raw_gma).c_str(),
                               target, requestId)) {
            return;
          }
          // lenc
          if (!dispatchIdValue(json, "lenc", String(status.lenc).c_str(),
                               target, requestId)) {
            return;
          }
          // vflip
          if (!dispatchIdValue(json, "vflip", String(status.vflip).c_str(),
                               target, requestId)) {
            return;
          }
          // hmirror
          if (!dispatchIdValue(json, "hmirror", String(status.hmirror).c_str(),
                               target, requestId)) {
            return;
          }
          // dcw
          if (!dispatchIdValue(json, "dcw", String(status.dcw).c_str(), target,
                               requestId)) {
            return;
          }
          // colorbar
          if (!dispatchIdValue(json, "colorbar",
                               String(status.colorbar).c_str(), target,
                               requestId)) {
            return;
          }
#if CAM_LED_PIN != -1
          // light
          if (!dispatchIdValue(
                  json, "light",
                  String(digitalRead(CAM_LED_PIN) == HIGH ? 1 : 0).c_str(),
                  target, requestId)) {
            return;
          }
#endif  // CAM_LED_PIN
        }
        if (json) {
          if (!dispatch("]}", target, requestId, ESP3DMessageType::tail)) {
            esp3d_log_e("Error sending answer to clients");
          }
        } else {
          {
            tmpstr = "ok\n";
            if (!dispatch(tmpstr.c_str(), target, requestId,
                          ESP3DMessageType::tail)) {
              esp3d_log_e("Error sending answer to clients");
            }
          }
        }
        return;
      } else {
        size_t s = sizeof(camcmd) / sizeof(const char*);
        for (size_t i = 0; i < s; i++) {
          String label = camcmd[i];
          label += "=";
          tmpstr = get_param(msg, cmd_params_pos, label.c_str());
          if (tmpstr.length() > 0) {
            int r = esp3d_camera.command(camcmd[i], tmpstr.c_str());
            if (r == -1) {
              hasError = true;
              error_msg = "Unknow command";
              esp3d_log_e("%s", error_msg.c_str());
            } else if (r == 1) {
              hasError = true;
              error_msg = "Invalid value";
              esp3d_log_e("%s", error_msg.c_str());
            } else {
              ok_msg = "ok";
            }
          }
        }
      }
    }
  }

  if (!dispatchAnswer(msg, COMMAND_ID, json, hasError,
                      hasError ? error_msg.c_str() : ok_msg.c_str())) {
    esp3d_log_e("Error sending response to clients");
  }

  /*
  bool noError = true;
  bool json = has_tag(cmd_params, "json");
  String response;
  String parameter;
  int errorCode = 200;  // unless it is a server error use 200 as default and
                        // set error in json instead

  #ifdef AUTHENTICATION_FEATURE
  if (auth_type == guest) {
    response = format_response(COMMANDID, json, false,
                               "Guest user can't use this command");
    noError = false;
    errorCode = 401;
  }
  #else
  (void)auth_type;
  #endif  // AUTHENTICATION_FEATURE
  if (noError) {
    if (!esp3d_camera.started()) {
      response =
          format_response(COMMANDID, json, false, "No camera initialized");
      noError = false;
    } else {
      parameter = clean_param(get_param(cmd_params, ""));
      // get
      if (parameter.length() == 0) {
        sensor_t* s = esp_camera_sensor_get();
        if (s == nullptr) {
          response =
              format_response(COMMANDID, json, false, "No camera
  initialized"); noError = false; } else { String line = ""; if (json) {
            esp3dmsg->print("{\"cmd\":\"170\",\"status\":\"ok\",\"data\":\"[");
          }
          // framesize
          if (json) {
            line += "{\"id\":\"framesize\",\"value\":\"";
          } else {
            line += "framesize:";
          }
          line += s->status.framesize;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // quality
          if (json) {
            line += "{\"id\":\"quality\",\"value\":\"";
          } else {
            line += "quality:";
          }
          line += s->status.quality;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // brightness
          if (json) {
            line += "{\"id\":\"brightness\",\"value\":\"";
          } else {
            line += "brightness:";
          }
          line += s->status.brightness;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // contrast
          if (json) {
            line += "{\"id\":\"contrast\",\"value\":\"";
          } else {
            line += "contrast:";
          }
          line += s->status.contrast;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // saturation
          if (json) {
            line += "{\"id\":\"saturation\",\"value\":\"";
          } else {
            line += "saturation:";
          }
          line += s->status.saturation;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // sharpness
          if (json) {
            line += "{\"id\":\"sharpness\",\"value\":\"";
          } else {
            line += "sharpness:";
          }
          line += s->status.sharpness;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // special_effect
          if (json) {
            line += "{\"id\":\"special_effect\",\"value\":\"";
          } else {
            line += "special_effect:";
          }
          line += s->status.special_effect;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // wb_mode
          if (json) {
            line += "{\"id\":\"wb_mode\",\"value\":\"";
          } else {
            line += "wb_mode:";
          }
          line += s->status.wb_mode;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // awb
          if (json) {
            line += "{\"id\":\"awb\",\"value\":\"";
          } else {
            line += "awb:";
          }
          line += s->status.awb;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // awb_gain
          if (json) {
            line += "{\"id\":\"awb_gain\",\"value\":\"";
          } else {
            line += "awb_gain:";
          }
          line += s->status.awb_gain;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // aec
          if (json) {
            line += "{\"id\":\"aec\",\"value\":\"";
          } else {
            line += "aec:";
          }
          line += s->status.aec;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // aec2
          if (json) {
            line += "{\"id\":\"aec2\",\"value\":\"";
          } else {
            line += "aec2:";
          }
          line += s->status.aec2;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // ae_level
          if (json) {
            line += "{\"id\":\"ae_level\",\"value\":\"";
          } else {
            line += "ae_level:";
          }
          line += s->status.ae_level;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // aec_value
          if (json) {
            line += "{\"id\":\"aec_value\",\"value\":\"";
          } else {
            line += "aec_value:";
          }
          line += s->status.aec_value;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // agc
          if (json) {
            line += "{\"id\":\"agc\",\"value\":\"";
          } else {
            line += "agc:";
          }
          line += s->status.agc;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // agc_gain
          if (json) {
            line += "{\"id\":\"agc_gain\",\"value\":\"";
          } else {
            line += "agc_gain:";
          }
          line += s->status.agc_gain;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // gainceiling
          if (json) {
            line += "{\"id\":\"gainceiling\",\"value\":\"";
          } else {
            line += "gainceiling:";
          }
          line += s->status.gainceiling;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // bpc
          if (json) {
            line += "{\"id\":\"bpc\",\"value\":\"";
          } else {
            line += "bpc:";
          }
          line += s->status.bpc;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // wpc
          if (json) {
            line += "{\"id\":\"wpc\",\"value\":\"";
          } else {
            line += "wpc:";
          }
          line += s->status.wpc;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // raw_gma
          if (json) {
            line += "{\"id\":\"raw_gma\",\"value\":\"";
          } else {
            line += "raw_gma:";
          }
          line += s->status.raw_gma;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // lenc
          if (json) {
            line += "{\"id\":\"lenc\",\"value\":\"";
          } else {
            line += "lenc:";
          }
          line += s->status.lenc;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // vflip
          if (json) {
            line += "{\"id\":\"vflip\",\"value\":\"";
          } else {
            line += "vflip:";
          }
          line += s->status.vflip;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // hmirror
          if (json) {
            line += "{\"id\":\"hmirror\",\"value\":\"";
          } else {
            line += "hmirror:";
          }
          line += s->status.hmirror;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // dcw
          if (json) {
            line += "{\"id\":\"dcw\",\"value\":\"";
          } else {
            line += "dcw:";
          }
          line += s->status.dcw;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
          // colorbar
          if (json) {
            line += "{\"id\":\"colorbar\",\"value\":\"";
          } else {
            line += "colorbar:";
          }
          line += s->status.colorbar;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
  #if CAM_LED_PIN != -1
          // light
          if (json) {
            line += "{\"id\":\"light\",\"value\":\"";
          } else {
            line += "light:";
          }
          line += digitalRead(CAM_LED_PIN) == HIGH ? 1 : 0;
          if (json) {
            line += "\"}";
            esp3dmsg->print(line.c_str());
          } else {
            esp3dmsg->printMSGLine(line.c_str());
          }
          line = "";
  #endif  // CAM_LED_PIN
          if (json) {
            esp3dmsg->printLN("]}");
          }
          return true;
        }
      } else {  // set
  #ifdef AUTHENTICATION_FEATURE
        if (auth_type != admin) {
          response = format_response(COMMANDID, json, false,
                                     "Wrong authentication level");
          noError = false;
          errorCode = 401;
        }
  #endif  // AUTHENTICATION_FEATURE
        if (noError) {
          String label = get_label(parameter.c_str(), "=");
          if (label.length() == 0) {
            response =
                format_response(COMMANDID, json, false, "Missing command");
            noError = false;
          } else {
            String labels = label + "=";
            String value = get_param(cmd_params, labels.c_str());
            if (value.length() == 0) {
              response =
                  format_response(COMMANDID, json, false, "Invalid value");
              noError = false;
            }
            if (noError) {
              int r = esp3d_camera.command(label.c_str(), value.c_str());
              if (r == -1) {
                response =
                    format_response(COMMANDID, json, false, "Unknow command");
                noError = false;
              } else if (r == 1) {
                response =
                    format_response(COMMANDID, json, false, "Invalid value");
                noError = false;
              } else {
                response = format_response(COMMANDID, json, true, "ok");
              }
            }
          }
        }
      }
    }
  }
  if (json) {
    esp3dmsg->printLN(response.c_str());
  } else {
    if (noError) {
      esp3dmsg->printMSG(response.c_str());
    } else {
      esp3dmsg->printERROR(response.c_str(), errorCode);
    }
  }
  return noError;*/
}

#endif  // CAMERA_DEVICE
