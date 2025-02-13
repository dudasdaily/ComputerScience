package Chap10;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.event.*;

public class Chap10_ex01 extends JFrame{
    Chap10_ex01() {
        // 1) 화면 구성
        setTitle("이벤트 처리 예제");
        setSize(300, 100);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // 2) 이벤트 소스(컴포넌트) 생성
        Container c = getContentPane(); // 컨테이너 생성
        c.setLayout(new FlowLayout()); // 기본값은 BoarderLayout이기 때문에 FlowLayout()으로 바꿔줌
        JButton btn = new JButton("Action"); // 버튼 컴포넌트 객체 생성
        c.add(btn); // 컨테이너에 컴포넌트를 집어넣음

        JButton btn2 = new JButton("블루베리");
        c.add(btn2);

        JLabel lb = new JLabel("Hello");
        c.add(lb);


        // 3) 리스너 달아주기
        btn.addActionListener(new MyActionListner()); // 이벤트 리스너 달기
        // 익명 클래스로 이벤트 리스너 달기
        btn2.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 이벤트 발생 객체 가져옴
                // e.getSource(); // Object를 반환 -> 레퍼런스가 정확히 누구인지 모름. 즉 버튼인지 레이블인지 체크박스인지 모름
                
                // 일단은 JButton이라고 가정
                JButton btn = (JButton)e.getSource();
        
                // 버튼의 문자열을 통해 특정
                if(btn.getText().equals("Action")) {
                    btn.setText("액션");
                }
                // 버튼의 문자열이 "Action"이 아닌 모든 버튼은 Text를 "Action"로
                else  {
                    btn.setText("Action");
                }
            }
        });

        c.addMouseListener(new MyMouseListener());

        

        setVisible(true);
    }
    public static void main(String[] args){
        new Chap10_ex01();
    }
}

// 독립 클래스로 이벤트 리스너 정의
class MyActionListner implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent e) {
        // 이벤트 발생 객체 가져옴
        // e.getSource(); // Object를 반환 -> 레퍼런스가 정확히 누구인지 모름. 즉 버튼인지 레이블인지 체크박스인지 모름
        
        // 일단은 JButton이라고 가정
        JButton btn = (JButton)e.getSource();

        // 버튼의 문자열을 통해 특정
        if(btn.getText().equals("Action")) {
            btn.setText("액션");
        }
        // 버튼의 문자열이 "Action"이 아닌 모든 버튼은 Text를 "Action"로
        else  {
            btn.setText("Action");
        }
    }

}

class MyMouseListener implements MouseListener {
    @Override
    // 마우스 클릭을 하면 그 위치로 레이블을 옮길거임.
    public void mouseClicked(MouseEvent e) {
        int x = e.getX();
        int y = e.getY();

        // 레이블 lb의 위치를 옮김
        Container c = (Container)e.getSource();
    }

    @Override
    public void mouseEntered(MouseEvent e) {
        
    }

    @Override
    public void mouseExited(MouseEvent e) {
        
    }

    @Override
    public void mousePressed(MouseEvent e) {
        
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        
    }

}