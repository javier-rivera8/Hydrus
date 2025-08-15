import json
import time
from testing import ThrusterController 

class MissionRunner:
    def __init__(self, mission_file, port='/dev/ttyACM0'):
        self.mission_file = mission_file
        self.controller = ThrusterController(port=port)
        self.mission_steps = []
        self.current_step = 0
    
    def load_mission(self):
        with open(self.mission_file, 'r') as f:
            self.mission_steps = json.load(f)
        print(f"Misión cargada con {len(self.mission_steps)} pasos")
    
    def run(self):
        while self.current_step < len(self.mission_steps):
            command = self.mission_steps[self.current_step]
            print(f"\nRunning paso {self.current_step+1}/{len(self.mission_steps)}: {command}")
            
            try:
                self.controller.execute_commands([command])
                self.current_step += 1
            except KeyboardInterrupt:
                print("\n Misión paused")
                break
        
        if self.current_step >= len(self.mission_steps):
            print("\n Mision completda")
    
    def close(self):
        self.controller.close()


if __name__ == "__main__":
    runner = MissionRunner(mission_file='mission.json', port='/dev/ttyACM0')
    runner.load_mission()
    runner.run()
    runner.close()
