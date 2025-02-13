package com.web.chap03.chap03;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import java.util.ArrayList;

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

    @GetMapping("/ex03")
    public String ex03() {
        return "ex03";
    }

    @PostMapping("/ex03/answer")
    public String ex03Answer(@RequestParam("mname") String mname, @RequestParam("color") String color, Model mo) {
        mo.addAttribute("mname", mname);
        mo.addAttribute("color", color);
        return "ex03Answer";
    }

    @GetMapping("/ex04")
    public String ex04(Model mo)
    {
        var arr = new ArrayList<String>();

        arr.add("고흐");
        arr.add("james");
        arr.add("dooli");
        arr.add("bread");

        mo.addAttribute("arr", arr);

        return "ex04";
    }    
}
