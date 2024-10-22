package web.middle.chap01;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;


@Controller
public class MyController {
    @GetMapping("/")
    public String home() {
        return "home";
    }

    @GetMapping("/login")
    public String login() {
        return "login";
    }

    @GetMapping("/register")
    public String register() {
        return "register";
    }
    
    @GetMapping("/memberTable")
    public String memberTable() {
        return "memberTable";
    }

    @GetMapping("/practice")
    public String practice() {
        return "practice";
    }
}