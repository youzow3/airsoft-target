#pragma once

struct IBase {
  public:
    virtual bool update() = 0;
};

class Target : IBase {
  public:
    Target(uint8_t led, uint8_t sensor);
    bool update() override;
    uint8_t led() { return led_; }
    uint8_t sensor() { return sensor_; }
    unsigned long last_fired() { return last_fired_; }
  private:
    uint8_t led_;
    uint8_t sensor_;
    unsigned long last_fired_;
};

class Game : IBase {
  public:
    Game(Target *targets, size_t ntargets) : targets_(targets), ntargets_(ntargets) {}
    virtual bool update() = 0;
  protected:
    Target *targets_;
    size_t ntargets_;
};

class GameTimeattack : public Game {
  public:
    GameTimeattack(Target *targets, size_t ntargets, size_t count);
    bool update() override;
  private:
    size_t *sequence_;
    size_t count_;
    size_t step_;
    bool stepped_;
};

struct LED {
  uint8_t led; // Pin number
  int level; // HIGH or LOW
  unsigned long timing; // Absolute timing in milliseconds.
};

class LEDBuffer : IBase {
  public:
    LEDBuffer(size_t bufsize);
    void add(const LED *action);
    bool update() override;
  private:
    const LED **buffer_;
    size_t buffer_size_;
    size_t start_;
    size_t end_;
};

extern LEDBuffer g_led_buffer;
