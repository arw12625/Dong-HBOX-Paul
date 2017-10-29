/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dong;

import control.ControlMap;
import io.ControllerInputMap;
import io.GameController;
import java.nio.file.Paths;
import ui.Console;

/**
 *
 * @author Andrew_2
 */
public class DriveTest {
    public static void main(String[] args) {
        
        GameController gc = GameController.getGameCubeController(0);

        GameController.startGameControllerThread(gc);
        
        //need to fix file loading / class loader / jar
        ControllerInputMap cim = ControllerInputMap.loadGamecubeInputMap();
        cim.setGameController(gc);
        
        ControlMap cm = ControlMap.loadControlMap(Paths.get("res/turnControl.json"));
        cm.setInputMap(cim);
        
        Console c = new Console("Drive Test");
        
        SimpleDrive sd = new SimpleDrive(cm);
        sd.setWriter(c.getWriter());
        c.setReader(sd.getReader());
        
        
        Thread lo = new Thread(new Runnable() {
            @Override
            public void run() {

                long last = System.currentTimeMillis();
                while (true) {
                    long time = System.currentTimeMillis();
                    if (time - last > 100) {
                        last = time;
                        sd.drive();
                    }
                    Thread.yield();
                }
            }
        });
        lo.start();
        
        
    }
}
