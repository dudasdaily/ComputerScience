package web.worldcup;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;

import jakarta.servlet.http.HttpSession;

@Controller
public class MyController {
    @Autowired
    starRep srep;

    @Autowired
    memberRep mrep;

    @GetMapping("/star/1")
    public String fisrt() {
        return "first";
    }

    @GetMapping("/star/2")
    public String second(HttpSession se, @RequestParam("firstWinner") String firstWinner) {
        se.setAttribute("firstWinner", firstWinner);

        return "second";
    }

    @GetMapping("/star/3")
    public String finalMetch(Model mo, HttpSession se, @RequestParam("secondWinner") String secondWinner){
        mo.addAttribute("firstWinner", se.getAttribute("firstWinner"));
        mo.addAttribute("secondWinner", secondWinner);

        return "finalMatch";
    }
    
    @GetMapping("/star/congratulations")
    public String congratulations(Model mo, @RequestParam("finalWinner") String finalWinner){
        mo.addAttribute("finalWinner", finalWinner);
        srep.increaseFcount(finalWinner);

        return "congratulations";
    }
    
    @GetMapping("/star/result")
    public String result(Model mo) {
        mo.addAttribute("arr", srep.findAll());
        return "result";
    }
    
    @GetMapping("/star/reset")
    public String reset() {
        srep.resetFcount();

        return "redirect:/star/result";
    }

    @GetMapping("/member/new")
    public String signIn() {
        return "signIn";
    }

    @GetMapping("/member/insert")
    public String memberCheck(@RequestParam("mid") String mid, @RequestParam("pw") String pw,
                              @RequestParam("name") String name, @RequestParam("phone") String phone, Model mo)
    {
        if(mrep.existsById(mid)) {
            mo.addAttribute("msg", mid + "는 이미 있는 아이디입니다.");
            mo.addAttribute("url", "back");
        }

        else {
            member obj = new member();
            obj.mid = mid;
            obj.pw = pw;
            obj.name = name;
            obj.phone = phone;
            obj.mileage = 0;

            mrep.save(obj);

            mo.addAttribute("msg", mid + "님 회원가입을 축하합니다.");
            mo.addAttribute("url", "/member/list");
        }
        return "popup";
    }

    @GetMapping("/")
    public String test(Model mo) {
        mo.addAttribute("arr", srep.findAll());

        return "test";
    }
    
}
