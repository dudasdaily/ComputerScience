package web.surbey;

import org.springframework.data.jpa.repository.JpaRepository;

public interface surveyRep extends JpaRepository<survey, Integer>{
    
}
