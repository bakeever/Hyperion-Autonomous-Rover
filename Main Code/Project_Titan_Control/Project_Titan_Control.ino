#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

int activeMission = 1; // Default to Mission 1

void setup()
{
  GD.begin();
}

void loop()
{
  GD.get_inputs(); // Read touch inputs

  // Update activeMission when a button is pressed
  if (GD.inputs.tag > 0) {
    activeMission = GD.inputs.tag; // Set the selected mission
  }

  GD.ClearColorRGB(0x202020); // Dark Gray Background for Retro CRT Look
  GD.Clear();

  // Title using default Font 24
  GD.cmd_text(230, 15, 24, OPT_CENTER, "Hyperion Control Center");

  // Draw a beige-colored box for the mission UI
  GD.ColorRGB(0xD8C3A5);  // Beige color
  GD.Begin(RECTS);
  GD.Vertex2ii(160, 40);  // Top-left corner
  GD.Vertex2ii(460, 250); // Bottom-right corner

  // ==== NEON GLOW EFFECT FOR BUTTONS ====
  // Draw a slightly larger, semi-transparent rectangle behind each button to create a glow effect
  GD.ColorRGB(0x00FFFF); // Neon Cyan Glow
  GD.ColorA(128); // Set transparency for glow effect (128 = 50% opacity)

  GD.Begin(RECTS); // Draw glow rectangles slightly larger than buttons
  GD.Vertex2ii(8, 48);  GD.Vertex2ii(152, 92);
  GD.Vertex2ii(8, 98);  GD.Vertex2ii(152, 142);
  GD.Vertex2ii(8, 148); GD.Vertex2ii(152, 192);
  GD.Vertex2ii(8, 198); GD.Vertex2ii(152, 242);

  GD.ColorA(255); // Reset transparency to full

  // ==== ACTUAL BUTTONS ====
  GD.ColorRGB(0x00FFFF); // Neon Cyan Buttons
  GD.Tag(1); GD.cmd_button(10, 50, 140, 40, 28, (activeMission == 1) ? OPT_FLAT : 0, "Mission 1");
  GD.Tag(2); GD.cmd_button(10, 100, 140, 40, 28, (activeMission == 2) ? OPT_FLAT : 0, "Mission 2");
  GD.Tag(3); GD.cmd_button(10, 150, 140, 40, 28, (activeMission == 3) ? OPT_FLAT : 0, "Mission 3");
  GD.Tag(4); GD.cmd_button(10, 200, 140, 40, 28, (activeMission == 4) ? OPT_FLAT : 0, "Mission 4");

  // Reset to black for text contrast
  GD.ColorRGB(0x000000);

  // Display GUI elements for the selected mission
  switch (activeMission) {
    case 1:
      GD.cmd_text(310, 80, 28, OPT_CENTER, "Mission 1: STATUS");
      GD.cmd_progress(200, 120, 200, 20, 0, 50, 100); // Progress bar (50%)
      GD.cmd_text(310, 160, 28, OPT_CENTER, "Sensors: ACTIVE");
      break;
    
    case 2:
      GD.cmd_text(310, 80, 28, OPT_CENTER, "Mission 2: CALIBRATING");
      GD.cmd_gauge(300, 150, 40, 0, 5, 10, 75, 100); // Fixed Gauge
      GD.cmd_text(310, 190, 28, OPT_CENTER, "Stabilization: GOOD");
      break;

    case 3:
      GD.cmd_text(310, 80, 28, OPT_CENTER, "Mission 3: NAVIGATION");
      GD.cmd_slider(200, 120, 200, 20, 0, 30, 100); // Slider at 30%
      GD.cmd_text(310, 160, 28, OPT_CENTER, "Direction: EAST");
      break;

    case 4:
      GD.cmd_text(310, 80, 28, OPT_CENTER, "Mission 4: ANALYSIS");
      GD.cmd_clock(300, 160, 40, 0, 3, 45, 20, 500); // Fixed Clock
      GD.cmd_text(310, 200, 28, OPT_CENTER, "Data Sync: 72%");
      break;
  }

  GD.swap();
}
