/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dong;

import comm.BufferReaderCallback;
import comm.BufferWriter;
import control.ControlMap;
import java.io.IOException;
import java.nio.ByteBuffer;

/**
 *
 * @author Andrew_2
 */
public class SimpleDrive {

    private ControlMap cm;
    private BufferReaderCallback reader;
    private BufferWriter writer;
    private ByteBuffer b;

    private final static short maxrange = 300;

    public SimpleDrive(ControlMap cm) {
        this.cm = cm;
        b = ByteBuffer.allocate(254);
        reader = new BufferReaderCallback() {
            @Override
            public void readBuffer(ByteBuffer msg) {
                
            }
        };
    }
    
    public BufferReaderCallback getReader() {
        return reader;
    }
    
    public void setWriter(BufferWriter writer) {
        this.writer = writer;
    }

    public void drive() {
        if (writer != null) {
            float forward = cm.getValue("FORWARD");
            float turn = cm.getValue("TURN");
            float throttle = (1 + cm.getValue("THROTTLE"))/2;
            System.out.println("THROT " + throttle);
            
            short left = (short) (maxrange * throttle * normalize(forward - turn));
            short right = (short) (maxrange * throttle * normalize(forward + turn));
            System.out.println("LEFT " + left);
            b.clear();

            b.put((byte) 'c');
            b.put((byte) 1);
            b.putShort(left);
            b.putShort(right);

            b.flip();
            try {
                writer.write(b);
            } catch (IOException ex) {
                System.err.println("Could not send msg");
            }
            b.rewind();
            
            
            float sweepIn = cm.getValue("SWEEP_IN");
            float sweepOut = cm.getValue("SWEEP_OUT");
            
            b.clear();
            byte dir = 0;
            if(sweepIn > 0.5f) {
                dir = 1;
            } else if(sweepOut > 0.5f) {
                dir = 2;
            }
            
            b.put((byte) 's');
            b.put((byte) 1);
            b.put(dir);

            b.flip();
            try {
                writer.write(b);
            } catch (IOException ex) {
                System.err.println("Could not send msg");
            }
            b.rewind();
        }
    }

    public float normalize(float val) {
        return clamp(val, -1, 1);
    }

    public float clamp(float val, float min, float max) {
        return Math.min(Math.max(val, min), max);
    }

}
