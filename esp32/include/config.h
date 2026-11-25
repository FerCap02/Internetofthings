#pragma once
#if __has_include("config.local.h")
#include "config.local.h"
#else
#include "config.example.h"
#endif

// Existing local configs can omit the optional default network.
#ifndef WIFI_DEFAULT_SSID
#define WIFI_DEFAULT_SSID ""
#endif
#ifndef WIFI_DEFAULT_PASSWORD
#define WIFI_DEFAULT_PASSWORD ""
#endif
