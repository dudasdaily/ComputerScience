package web.worldcup;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;

import jakarta.servlet.http.HttpSession;


@Controller
public class MyController {
    @GetMapping("/")
    public String m1() {
        return "match1";
    }
    
    @GetMapping("/star/1")
    public String m2(HttpSession se, @RequestParam("firstWinner") String firstWinner) {
        se.setAttribute("firstWinner", firstWinner);
        
        return "match2";
    }
    
    @GetMapping("/star/3")
    public String m3(HttpSession se, @RequestParam("secondWinner") String secondWinner, Model mo) {
        mo.addAttribute("firstWinner", se.getAttribute("firstWinner"));
        mo.addAttribute("secondWinner", secondWinner);

        return "finalMatch";
    }
}
