package web.diary;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;


@Controller
public class diaryController {
    @Autowired private diaryRep drep;

    @GetMapping("/diary")
    public String diary() {
        
        return "diary";
    }

    @GetMapping("/diaryPop")
    public String diaryPop() {
        return "diaryPop";
    }
    
    @GetMapping("/diary/insert")
    public String diaryInsert(@RequestParam("title") String title, @RequestParam("content") String content) {
        diary m = new diary();
        m.title = title;
        m.content = content;

        drep.save(m);

        return "redirect:/diaryPop";
    }

    @GetMapping("/diaryList")
    public String diaryList(Model mo) {
        mo.addAttribute("arr", drep.findAll());

        return "diaryList";
    }
    
}
