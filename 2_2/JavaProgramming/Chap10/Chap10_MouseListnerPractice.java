package Chap10;

import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.*;

public class Chap10_MouseListnerPractice extends JFrame{
    JLabel[] lbKeys = new JLabel[3];
    JLabel lb = new JLabel();

    Chap10_MouseListnerPractice() {
        setTitle("practice");
        setSize(300, 100);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        Container c = getContentPane();
        c.setLayout(new FlowLayout());

        lb.setText("Hello");

        lbKeys[0] = new JLabel("getKeyCode() : ");
        lbKeys[1] = new JLabel("getKeyChar() : ");
        lbKeys[2] = new JLabel("getKeyText() : ");
        
        for(JLabel k : lbKeys) {
            c.add(k);
        }

        c.addKeyListener(new Key_adap());
        
        setVisible(true);

        c.setFocusable(true);
        c.requestFocus();
    }

    class Key_adap extends KeyAdapter {
        @Override
        public void keyPressed(KeyEvent e) {
            System.out.println("KeyPressed");

            Container c = (Container)e.getSource();
            char keyChar = e.getKeyChar();
            int keyCode = e.getKeyCode();

            lbKeys[0].setText("getKeyCode() : " + keyCode); 
            lbKeys[1].setText("getKeyChar() : " + keyChar);
            lbKeys[2].setText("getKeyText() : " + KeyEvent.getKeyText(keyCode));

            if(keyCode == KeyEvent.VK_SHIFT) {
                c.setBackground(Color.green);
            }
            else if(keyChar == '#') {
                c.setBackground(Color.yellow);
            }
            else {
                c.setBackground(null);
            }

            int move_step = 10;

        }

        @Override
        public void keyReleased(KeyEvent e) {
            System.out.println("KeyReleased");
        }

        @Override
        public void keyTyped(KeyEvent e) {
            System.out.println("KeyTyped");
        }
    }

    public static void main(String[] args) {
        new Chap10_MouseListnerPractice();
    }
}
