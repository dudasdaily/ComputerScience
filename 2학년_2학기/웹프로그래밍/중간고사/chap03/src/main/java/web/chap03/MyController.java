package web.chap03;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.PostMapping;

@Controller
public class MyController {
    @GetMapping("/")
    public String index() {
        return "index";
    }

    @GetMapping("/ex01")
    public String ex01() {
        return "ex01";
    }

    @PostMapping("/ex01/answer")   
    public String ex01Answer(@RequestParam(name = "id") String id, Model mo) {
        mo.addAttribute("id", id);       
        return "ex01Answer";
    }
    
    

}
