package com.web.chap03.chap03;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;


@Controller
public class MyController {
    
    @GetMapping("/")
    public String home()
    {
        return "home";
    }

    @GetMapping("/ex01")
    public String ex01()
    {
        return "ex01";
    }

    @PostMapping("/ex01/answer")
    public String ex01Answer(@RequestParam(name="name") String name, Model mo)
    {
        mo.addAttribute("name", name);
        return "ex01Answer";
    }

}
