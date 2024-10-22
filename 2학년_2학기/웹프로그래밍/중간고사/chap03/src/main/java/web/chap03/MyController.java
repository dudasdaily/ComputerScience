package web.chap03;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;


@Controller
public class MyController {
    @GetMapping("/")
    public String index() {
        return "index";
    }
    
    
}
