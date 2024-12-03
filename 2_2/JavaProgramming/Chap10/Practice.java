import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.*;

public class Practice extends JFrame {
    JLabel[] labels = new labels[3];

    Practice() {
        Container c = getContentPane();
        setTitle("test");
        setSize(300, 100);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        c.setLayout(new FlowLayout());
        
        labels[0].setText("getKeyCode() : ");
        labels[1].setText("getKeyChar() : ");
        labels[2].setText("getKeyText() : ");

        for(JLabel k : labels) {
            c.add(k);    
        }

        c.addKeyListener(new MyKeyListener());

        setVisible(true);
    }

    public static void main(String[] args) {
        Practice a = new Practice();
    }

    public class MyKeyListener extends KeyAdapter {
        @Override
        public void keyPressed(KeyEvent e) {
            int KeyCode = e.getKeyCode();
            char KeyChar = e.getKeyChar();

            labels[0].setText("getKeyCode() : " + KeyCode);
            labels[1].setText("getKeyChar() : " + KeyChar);
            labels[2].setText("getKeyText() : " + KeyEvent.getKeyText(KeyCode));

            
        }

        @Override
        public void keyReleased(KeyEvent e) {
        }

        @Override
        public void keyTyped(KeyEvent e) {
        }
    
    }
}


