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
    
    @GetMapping("/bread")
    public String bread()    
    {
        return "bread";
    }

    @PostMapping("/bread/answer")
    public String breadAnswer(@RequestParam("bread") String bread, @RequestParam("price") Integer price, @RequestParam("amount") Integer amount, Model mo)
    {
        mo.addAttribute("bread", bread);
        mo.addAttribute("amount", amount);
        mo.addAttribute("price", price * amount);

        return "breadAnswer";
    }


}
