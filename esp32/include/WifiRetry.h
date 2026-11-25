#pragma once
#include <stdint.h>

// A single owner starts connections; a retry waits for the previous attempt
// to finish or be explicitly cancelled before touching the Wi-Fi driver.
class WifiRetry {
 public:
  static constexpr uint32_t MIN_DELAY_MS=2000, MAX_DELAY_MS=10000, ATTEMPT_MS=8000;
  explicit WifiRetry(uint32_t now) : finishedAt(now) {}
  bool ready(uint32_t now,bool portalActive,bool connected) const {
    return !portalActive && !connected && !active && uint32_t(now-finishedAt)>=delayMs;
  }
  void start(uint32_t now) { active=true; startedAt=now; }
  bool expired(uint32_t now) const { return active && uint32_t(now-startedAt)>=ATTEMPT_MS; }
  void failed(uint32_t now) {
    active=false; finishedAt=now;
    delayMs=delayMs<MAX_DELAY_MS/2 ? delayMs*2 : MAX_DELAY_MS;
  }
  void reset(uint32_t now) { active=false; finishedAt=now; delayMs=MIN_DELAY_MS; }
  uint32_t delay() const { return delayMs; }
 private:
  bool active=false;
  uint32_t finishedAt,startedAt=0,delayMs=MIN_DELAY_MS;
};
