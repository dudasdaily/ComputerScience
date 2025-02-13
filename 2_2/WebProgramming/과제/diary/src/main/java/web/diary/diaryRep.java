package web.diary;

import org.springframework.data.jpa.repository.JpaRepository;

public interface diaryRep extends JpaRepository<diary, Integer>{
    
}
