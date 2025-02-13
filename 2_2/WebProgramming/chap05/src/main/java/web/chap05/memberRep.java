package web.chap05;

import org.springframework.data.jpa.repository.JpaRepository;

public interface memberRep extends JpaRepository<member, String>
{
    
} 