package com.web.wise;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.PostMapping;



@Controller
public class MyController {
    @GetMapping("/")
    public String wise()
    {
        return "wise";
    }

    @PostMapping("wise/answer")
    public String wiseAnswer(@RequestParam("name") String name, @RequestParam("phrase") String phrase, Model mo) {
        mo.addAttribute("name", name);
        mo.addAttribute("phrase", phrase);
        return "wiseAnswer";
    }
    


}
