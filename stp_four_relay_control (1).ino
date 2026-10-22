/*
 * STP Four-Relay Control System
 * =============================
 *
 * PROPOSED STARTING POINT — pin assignments are NOT VERIFIED against
 * the original sketch. Confirm every pin assignment against the original
 * design before wiring any hardware.
 *
 * Control logic:
 *   Four loads (Blower 1, MBBR, Sludge system, Blower 2) are sequenced
 *   through a configurable cycle. Each state has an independently
 *   configurable ON duration. The cycle repeats indefinitely.
 *
 * Hardware:
 *   - Arduino Uno R3
 *   - 4-channel relay module (optocoupler-isolated, active-low assumed)
 *   - 4x contactors driving the loads (wired via the relay dry contacts)
 *
 * Status: PROPOSED
 * Tested: NOT YET TESTED
 *
 * Released under the MIT License.
 */

// ---------------------------------------------------------------------------
// Pin assignments
// STATUS: NOT VERIFIED — these are placeholders.
// Confirm against the original sketch before wiring.
// ---------------------------------------------------------------------------
#define PIN_RELAY_BLOWER1   2
#define PIN_RELAY_MBBR       3
#define PIN_RELAY_SLUDGE     4
#define PIN_RELAY_BLOWER2    5

// ---------------------------------------------------------------------------
// Relay active level
// Most low-cost 4-channel relay modules are active-LOW (LOW = relay ON).
// If your module is active-HIGH, set this to false.
// STATUS: PROPOSED — verify against the actual relay module's datasheet.
// ---------------------------------------------------------------------------
#define RELAY_ACTIVE_LOW   true

// ---------------------------------------------------------------------------
// Cycle timing (milliseconds)
// STATUS: PROPOSED — these are example values, not validated process
// parameters. The original designer must set these to match the plant's
// biological process requirements.
// ---------------------------------------------------------------------------
#define TIME_IDLE_MS        5000UL
#define TIME_BLOWER1_MS     (15UL * 60UL * 1000UL)   // 15 minutes
#define TIME_MBBR_MS        (30UL * 60UL * 1000UL)   // 30 minutes
#define TIME_SLUDGE_MS      (10UL * 60UL * 1000UL)   // 10 minutes
#define TIME_BLOWER2_MS     (15UL * 60UL * 1000UL)   // 15 minutes
#define TIME_CYCLE_END_MS   10000UL

// ---------------------------------------------------------------------------
// State machine
// ---------------------------------------------------------------------------
enum CycleState {
  STATE_IDLE = 0,
  STATE_BLOWER1,
  STATE_MBBR,
  STATE_SLUDGE,
  STATE_BLOWER2,
  STATE_CYCLE_END
};

static CycleState currentState = STATE_IDLE;
static unsigned long stateEnterTime = 0;

// ---------------------------------------------------------------------------
// Helper: write a relay output, honouring the active-low assumption
// ---------------------------------------------------------------------------
static void writeRelay(uint8_t pin, bool on) {
  bool level = RELAY_ACTIVE_LOW ? !on : on;
  digitalWrite(pin, level ? HIGH : LOW);
}

// ---------------------------------------------------------------------------
// Helper: set all four relays OFF
// ---------------------------------------------------------------------------
static void allRelaysOff() {
  writeRelay(PIN_RELAY_BLOWER1, false);
  writeRelay(PIN_RELAY_MBBR,    false);
  writeRelay(PIN_RELAY_SLUDGE,  false);
  writeRelay(PIN_RELAY_BLOWER2, false);
}

// ---------------------------------------------------------------------------
// Helper: print current state to Serial Monitor
// ---------------------------------------------------------------------------
static const char* stateName(CycleState s) {
  switch (s) {
    case STATE_IDLE:       return "IDLE";
    case STATE_BLOWER1:    return "BLOWER1";
    case STATE_MBBR:       return "MBBR";
    case STATE_SLUDGE:     return "SLUDGE";
    case STATE_BLOWER2:    return "BLOWER2";
    case STATE_CYCLE_END:  return "CYCLE_END";
    default:               return "UNKNOWN";
  }
}

static void printState(CycleState s, unsigned long elapsed) {
  Serial.print(F("[STP] state="));
  Serial.print(stateName(s));
  Serial.print(F(" elapsed_ms="));
  Serial.print(elapsed);
  Serial.print(F(" next="));
  switch (s) {
    case STATE_IDLE:      Serial.println(F("BLOWER1")); break;
    case STATE_BLOWER1:   Serial.println(F("MBBR")); break;
    case STATE_MBBR:       Serial.println(F("SLUDGE")); break;
    case STATE_SLUDGE:    Serial.println(F("BLOWER2")); break;
    case STATE_BLOWER2:   Serial.println(F("CYCLE_END")); break;
    case STATE_CYCLE_END: Serial.println(F("IDLE (restart cycle)")); break;
    default:              Serial.println(F("?")); break;
  }
}

// ---------------------------------------------------------------------------
// Helper: enter a new state
// ---------------------------------------------------------------------------
static void enterState(CycleState next) {
  currentState = next;
  stateEnterTime = millis();
  allRelaysOff();
  switch (next) {
    case STATE_IDLE:       /* all off */ break;
    case STATE_BLOWER1:    writeRelay(PIN_RELAY_BLOWER1, true); break;
    case STATE_MBBR:       writeRelay(PIN_RELAY_MBBR,    true); break;
    case STATE_SLUDGE:     writeRelay(PIN_RELAY_SLUDGE,  true); break;
    case STATE_BLOWER2:    writeRelay(PIN_RELAY_BLOWER2, true); break;
    case STATE_CYCLE_END:  /* all off */ break;
  }
  printState(next, 0UL);
}

// ---------------------------------------------------------------------------
// Arduino setup
// ---------------------------------------------------------------------------
void setup() {
  pinMode(PIN_RELAY_BLOWER1, OUTPUT);
  pinMode(PIN_RELAY_MBBR,    OUTPUT);
  pinMode(PIN_RELAY_SLUDGE,  OUTPUT);
  pinMode(PIN_RELAY_BLOWER2, OUTPUT);
  allRelaysOff();

  Serial.begin(9600);
  Serial.println(F("[STP] controller boot"));
  Serial.println(F("[STP] WARNING: pin assignments are NOT VERIFIED."));
  Serial.println(F("[STP] WARNING: confirm against original sketch before wiring."));
  Serial.println(F("[STP] entering IDLE for safe startup."));

  enterState(STATE_IDLE);
}

// ---------------------------------------------------------------------------
// Arduino loop
// ---------------------------------------------------------------------------
void loop() {
  unsigned long now = millis();
  unsigned long elapsed = now - stateEnterTime;

  switch (currentState) {
    case STATE_IDLE:
      if (elapsed >= TIME_IDLE_MS)        enterState(STATE_BLOWER1);
      break;
    case STATE_BLOWER1:
      if (elapsed >= TIME_BLOWER1_MS)     enterState(STATE_MBBR);
      break;
    case STATE_MBBR:
      if (elapsed >= TIME_MBBR_MS)        enterState(STATE_SLUDGE);
      break;
    case STATE_SLUDGE:
      if (elapsed >= TIME_SLUDGE_MS)      enterState(STATE_BLOWER2);
      break;
    case STATE_BLOWER2:
      if (elapsed >= TIME_BLOWER2_MS)     enterState(STATE_CYCLE_END);
      break;
    case STATE_CYCLE_END:
      if (elapsed >= TIME_CYCLE_END_MS)   enterState(STATE_IDLE);
      break;
  }
}
