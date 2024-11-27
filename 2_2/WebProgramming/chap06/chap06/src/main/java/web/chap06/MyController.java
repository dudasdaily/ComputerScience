package web.chap06;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.PostMapping;

@Controller
public class MyController {
    @GetMapping("/")
    public String iam() {
        return "iam";
    }
    
    @PostMapping("/foods/report")
    public String iamAnswer(@RequestParam("gender") String gender, @RequestParam("age") Integer age,
                            @RequestParam(value = "foods", required = false) String[] foods, @RequestParam("maru") Integer maru,
                            @RequestParam("cat") Integer cat, @RequestParam("comments") String comments, Model mo) {
        mo.addAttribute("age", age);
        mo.addAttribute("gender", gender);
        mo.addAttribute("maru", maru);
        mo.addAttribute("cat", cat);
        mo.addAttribute("comments", comments);

        if(foods == null || foods.length == 0){            
            String[] food = {"좋아하는 음식이 없어요 ㅠ_ㅠ"};
            mo.addAttribute("foods", food);
        }
        
        else {
            mo.addAttribute("foods", foods);
        }
        
        return "iamAnswer";
    }
    
}
