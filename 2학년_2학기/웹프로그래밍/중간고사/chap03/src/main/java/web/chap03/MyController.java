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

    @GetMapping("/ex02")
    public String ex02() {
        return "ex02";
    }
    
    @PostMapping("/ex02/answer")
    public String ex02Answer(@RequestParam("name") String name, 
                             @RequestParam("position") String position, Model mo) {
        mo.addAttribute("name", name);
        mo.addAttribute("position", position);

        int salary = 0;
        switch(position) {
            case "사원" -> salary = 3500; 
            case "대리" -> salary = 5000; 
            case "팀장" -> salary = 7000; 
            case "임원" -> salary = 9900; 
        }
        mo.addAttribute("salary", salary);

        return "ex02Answer";
    }

    @GetMapping("/ex03")
    public String ex03() {
        return "ex03";
    }

    @PostMapping("/ex03/answer")
    public String ex03Answer(@RequestParam("name") String name,
                            @RequestParam("color") String color, Model mo) {
        
        mo.addAttribute("name", name);
        mo.addAttribute("color", color);
        return "ex03Answer";
    }
}
