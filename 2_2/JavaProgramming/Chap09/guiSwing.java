import javax.swing.*;
import java.awt.*;

public class guiSwing extends JFrame{
    public guiSwing() {
        setTitle("First GUI");
        // 이거 안하면 기본 크기는 0, 0
        setSize(300, 300);
        // 기본 값이 안보이는 걸로 되어있음.
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        // 컨텐트팬은 JFrame객체가 생성될 때 자동 생성
        // 프레임에 부착된 컨텐트팬 알아내기.
        Container contentPane = getContentPane();
        // contentPane.setLayout(new FlowLayout(FlowLayout.LEFT));
        FlowLayout fl = new FlowLayout(FlowLayout.LEFT);
        BorderLayout bl = new BorderLayout();

        contentPane.setLayout(bl);
        contentPane.setBackground(Color.ORANGE);
        
        // contentPane.add(new Button("OK"));
        // contentPane.add(new Button("Cancle"));
        // contentPane.add(new Button("Ignore"));

        contentPane.add(new Button("OK"));
        contentPane.add(new Button("Cancle"), BorderLayout.NORTH);
        contentPane.add(new Button("Ignore"), BorderLayout.SOUTH);
        
        setVisible(true);
    }   
    
    public static void main(String[] args) {
        new guiSwing();
        // guiSwing frame = new guiSwing();
    }
}