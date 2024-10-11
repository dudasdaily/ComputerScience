package com.web.employ;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.PostMapping;



@Controller
public class MyController {
    
    @GetMapping("")
    public String home()
    {
        return "q06";
    }

    @GetMapping("/q06/a")
    public String q06a()
    {
        return "q06a";
    }

    @GetMapping("/q06/b")
    public String q06b()
    {
        return "q06b";
    }

    @PostMapping("/q06/aa")
    public String q06aa(@RequestParam("firstCompany") String firstCompany, @RequestParam("secondCompany") String secondCompany,
                                Model mo)
    {
        mo.addAttribute("firstCompany", firstCompany);   
        mo.addAttribute("secondCompany", secondCompany);   
        return "q06aa";
    }

    @PostMapping("/q06/bb")
    public String q06bb(@RequestParam("job") String job, Model mo)
    {
        mo.addAttribute("job", job);
        return "q06bb";
    }
    
}
