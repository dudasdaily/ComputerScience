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
    public String ex01Answer(@RequestParam(name="name") String name, @RequestParam(name="pw") String pw, Model mo)
    { 
        mo.addAttribute("name", name);
        mo.addAttribute("pw", pw);
        return "ex01Answer";
    }

    @GetMapping("/ex02")
    public String ex02()
    {
        return "ex02";
    }
    
    @PostMapping("/ex02/answer")
    public String ex02Answer(@RequestParam(name="name") String name, @RequestParam(name="po") String po, Model mo)
    {
        mo.addAttribute("name", name);
        mo.addAttribute("po", po);

        int salary = 0;

        switch(po)
        {
            case "사원" -> salary = 3000;
            case "대리" -> salary = 5000;
            case "팀장" -> salary = 7000;
            case "임원" -> salary = 9000;
        }

        mo.addAttribute("salary", salary);
        return "ex02Answer";
    }

}
