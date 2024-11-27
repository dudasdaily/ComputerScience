package web.surbey;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

import jakarta.servlet.http.HttpSession;

@Controller
public class MyController {
    @Autowired private surveyRep sRep;

    @GetMapping("/login")
    public String login() {
        return "login";
    }

    @PostMapping("/surbey")
    public String surbey(HttpSession se, @RequestParam("id") String id) {
        se.setAttribute("id", id);
        return "surbey";
    }

    @PostMapping("/surbey2")
    public String surbey2(HttpSession se, @RequestParam("color") String color) {
        se.setAttribute("color", color);
        return "surbey2";
    }

    @PostMapping("/lipservice")
    public String postMethodName(HttpSession se,@RequestParam("os") String os) {
        se.setAttribute("os", os);

        return "lipservice";
    }

    @GetMapping("/result")
    public String result(HttpSession se, Model mo) {
        String id = (String)se.getAttribute("id");
        String color = (String)se.getAttribute("color");
        String os = (String)se.getAttribute("os");
        String f_color = "";

        switch (color) {
            case "빨간색" -> f_color = "red";
            case "파란색" -> f_color = "blue";
        }

        mo.addAttribute("id", id);
        mo.addAttribute("f_color", f_color);
        mo.addAttribute("color", color);
        mo.addAttribute("os", os);
        
        survey m = new survey();
        m.id = id;
        m.color = color;
        m.os = os;

        sRep.save(m);

        return "result";
    }

    @GetMapping("/surveyList")
    public String surveyList(Model mo) {
        mo.addAttribute("arr", sRep.findAll());
        
        return "surveyList";
    }
    
}
